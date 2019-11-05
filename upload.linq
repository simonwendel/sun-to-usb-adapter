<Query Kind="Program">
  <NuGetReference>System.IO.Ports</NuGetReference>
  <Namespace>System.IO.Ports</Namespace>
</Query>

public string ResetPort => "COM8";
public string ProgramPort => "COM9";
public string AvrDudeExecutable => @"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe";
public string AvrDudeConfig => @"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf";

void Main(string[] args)
{
	var filename = GetFilename(args);
	var programPort = GetProgramPort(args);
	if (programPort == null)
	{
		Console.WriteLine("Specify program port to upload");
		Environment.Exit(-2);
	}

	var resetPort = GetResetPort(args);
	if (resetPort != null)
	{
		Reset(resetPort);
	}
	
	Thread.Sleep(1000);
	
	Program(programPort, filename);
}

void Reset(string port)
{
	var serialPort = new SerialPort(port);
	serialPort.BaudRate = 1200;
	serialPort.Open();
	serialPort.Close();
}

void Program(string port, string file)
{
	var pi = new ProcessStartInfo
	{
		FileName = AvrDudeExecutable,
		Arguments = $"-C\"{AvrDudeConfig}\" -v -patmega32u4 -cavr109 -P{port} -b57600 -D -Uflash:w:{file}:i",
		RedirectStandardOutput = true,
		RedirectStandardError = true,
		UseShellExecute = false
	};

	var p = new Process();
	p.StartInfo = pi;

	p.OutputDataReceived += PrintOutput;
	p.ErrorDataReceived += PrintOutput;

	p.Start();
	p.BeginOutputReadLine();
	p.BeginErrorReadLine();
	p.WaitForExit();
}

string GetFilename(string[] args)
{
	if (args.Length < 1)
	{
		Console.WriteLine("Specify file to upload");
		Environment.Exit(-1);
	}

	return args.First();
}

string GetProgramPort(string[] args)
{
	if(args.Length >= 2)
	{
		return args[1];
	}
	
	return null;
}

string GetResetPort(string[] args)
{
	if (args.Length == 3)
	{
		return args[2];
	}

	return null;
}

void PrintOutput(object sender, DataReceivedEventArgs args)
{
	if(args.Data != null)
	{
		Console.WriteLine(args.Data);
	}
}