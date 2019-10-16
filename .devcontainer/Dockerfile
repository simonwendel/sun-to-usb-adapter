# Sun to USB keyboard adapter
# Copyright (C) 2019  Simon Wendel
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#==================================================================#
# An environment able to compile both Arduino code and Google Test #
# unit test fixtures.                                              #
#==================================================================#

FROM library/fedora:30 as dev

RUN dnf upgrade -y

# os stuff
RUN dnf group install -y "Minimal Install"
RUN dnf install -y which

# build stuff
RUN dnf group install -y "Development Tools"
RUN dnf install -y gcc-c++ gtest-devel gmock-devel

# special build stuff
ARG RPMFILE=arduino-mk-1.6.0-1.fc30.noarch.rpm
ARG GHLINK=https://github.com/simonwendel/configs/raw/master/Packages/${RPMFILE}
RUN dnf install -y arduino-core ${GHLINK}

# adafruit boards
RUN mkdir -p /usr/share/arduino/hardware/adafruit/avr/
WORKDIR /usr/share/arduino/hardware/adafruit/avr/
RUN git clone https://github.com/adafruit/Adafruit_Arduino_Boards.git . \ 
    && rm -rf .git/ .gitignore .gitmodules

# non-root user as per https://aka.ms/vscode-remote/containers/non-root-user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd -s /bin/bash --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} \
    && usermod -aG wheel ${USERNAME} \
    && passwd -d ${USERNAME} \
    && mkdir -p /home/${USERNAME}/.vscode-server /home/${USERNAME}/.vscode-server-insiders \
    && chown -R ${USER_UID}:${USER_GID} /home/${USERNAME} \
    && touch /home/${USERNAME}/.gitconfig

# for the vscode c++ extension builtin clang-format
RUN dnf install -y ncurses-compat-libs

USER ${USERNAME}
CMD [ "/bin/bash" ]
