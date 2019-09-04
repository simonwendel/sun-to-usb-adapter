<Query Kind="Program">
  <NuGetReference>System.IO.Ports</NuGetReference>
  <Namespace>System.IO.Ports</Namespace>
</Query>

public string ResetPort => "COM4";
public string ProgramPort => "COM3";
public string AvrDudeExecutable => @"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe";
public string AvrDudeConfig => @"C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf";

void Main(string[] args)
{
	var filename = GetFilename(args);
	
	Reset(ResetPort);
	Thread.Sleep(1000);
	
	Program(ProgramPort, filename);
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
	if (args.Length != 1)
	{
		Console.WriteLine("Specify file to upload");
		Environment.Exit(-1);
	}
	
	return args.First();
}

void PrintOutput(object sender, DataReceivedEventArgs args)
{
	if(args.Data != null)
	{
		Console.WriteLine(args.Data);
	}
}