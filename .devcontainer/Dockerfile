# Use stock Ubuntu 24.04 (Noble Numbat)
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV REFRESHED_AT=2025-08-18

RUN echo "deb http://security.ubuntu.com/ubuntu focal-security main universe" > /etc/apt/sources.list.d/ubuntu-focal-sources.list

# Install dependencies
RUN apt update \
    && apt -y install --no-install-recommends \
    python3-dev \
    python3-pip \
    git \
    cmake \
    ninja-build \
    gdb \
    automake \
    autoconf \
    usbutils \
    make \
    libncurses5 \
    build-essential \
    libtool \
    gcc-multilib \
    g++-multilib \
    bc \
    unzip \
    device-tree-compiler \
    tcl-dev \
    wget \
    ca-certificates \
    stlink-tools \
    openssh-client \
    && rm -rf /var/lib/apt/lists/*

# Update PIP and install Python tools
# RUN pip3 install --no-cache-dir --upgrade pip \
#     && pip3 install commitizen pycryptodome kconfiglib pre-commit

# # Set up a tools dev directory
WORKDIR /usr

# # Download and install ARM GNU toolchain
RUN wget -q --show-progress --progress=bar:force:noscroll --no-check-certificate \
    --output-document=gnu_gcc_arm.tar.xz \
    https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz \
    && tar -xJf gnu_gcc_arm.tar.xz \
    && rm gnu_gcc_arm.tar.xz

# # Extract the actual directory name and add to PATH
RUN TOOLCHAIN_DIR=$(find /usr -maxdepth 1 -type d -name "arm-gnu-toolchain*" -print -quit) \
    && echo "Found toolchain at: ${TOOLCHAIN_DIR}" \
    && echo "export PATH=${TOOLCHAIN_DIR}/bin:\$PATH" >> /etc/profile.d/arm-toolchain.sh

ENV PATH=/usr/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi/bin:$PATH

# Custom bash prompt
RUN echo "__bash_prompt() {\n" \
    "    local userpart='\`export XIT=\$? " \
    "        && [ ! -z \"\${GITHUB_USER}\" ] && echo -n \"\[\033[0;32m\]@\${GITHUB_USER} \" || echo -n \"\[\033[0;32m\]\u \" " \
    "        && [ \"\$XIT\" -ne \"0\" ] && echo -n \"\[\033[1;31m\]➜\" || echo -n \"\[\033[0m\]➜\"\`' \n" \
    "    local gitbranch='\`" \
    "        if [ \"\$(git config --get codespaces-theme.hide-status 2>/dev/null)\" != 1 ]; then " \
    "            export BRANCH=\$(git symbolic-ref --short HEAD 2>/dev/null || git rev-parse --short HEAD 2>/dev/null); " \
    "            if [ \"\${BRANCH}\" != \"\" ]; then " \
    "                echo -n \"\[\033[0;36m\](\[\033[1;31m\]\${BRANCH}\" " \
    "                && if git ls-files --error-unmatch -m --directory --no-empty-directory -o --exclude-standard \":/*\" > /dev/null 2>&1; then " \
    "                        echo -n \" \[\033[1;33m\]✗\"; " \
    "                fi " \
    "                && echo -n \"\[\033[0;36m\]) \";" \
    "            fi; " \
    "        fi\`'\n" \
    "    local lightblue='\[\033[1;34m\]'\n" \
    "    local removecolor='\[\033[0m\]'\n" \
    "    PS1=\"\${userpart} \${lightblue}\w \${gitbranch}\${removecolor}\\$ \"\n" \
    "    unset -f __bash_prompt\n" \
    "}\n" \
    "__bash_prompt" >> ~/.bashrc
