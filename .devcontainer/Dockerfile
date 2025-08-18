ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}
ARG VARIANT

ENV REFRESHED_AT 2023-02-15

# build commands to build and tag image (from root project directory):
# !!! DONT FORGET TO CHANGE TAG (VERSION) !!!
# docker login registry.gitlab.com -u dkrasutski
# <type your gitlab password>
# docker build -t registry.gitlab.com/dkrasutski/loko_air/loko:X.Y -f ./.devcontainer/Dockerfile .
# docker push registry.gitlab.com/dkrasutski/loko_air/loko:X.Y
# Manually build the Docker image: docker build -f .devcontainer/Dockerfile .

#Install CLang keys
# RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
# RUN echo "\n\n"\
#     "deb http://apt.llvm.org/focal/ llvm-toolchain-focal main\n"\
#     "deb-src http://apt.llvm.org/focal/ llvm-toolchain-focal main\n"\
#     "# 16\n"\
#     "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-16 main\n"\
#     "deb-src http://apt.llvm.org/focal/ llvm-toolchain-focal-16 main\n"\
#     "# 15\n"\
#     "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main\n"\
#     "deb-src http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main\n" >> /etc/apt/sources.list

RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends software-properties-common \    
    && apt-get -y install \
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
    && apt-get remove -y software-properties-common \
    && rm -rf /var/lib/apt/lists/*

# COPY ./.devcontainer/llvm.sh /opt/llvm.sh
# RUN /opt/llvm.sh

# Update PIP
RUN pip3 install --no-cache-dir --upgrade pip
RUN pip3 install commitizen pycryptodome kconfiglib pre-commit

# Set up a tools dev directory
WORKDIR /usr

# Download ARM GNU toolchain
                                                                                                                                
RUN wget -q --show-progress --progress=bar:force:noscroll --no-check-certificate --output-document=gnu_gcc_arm.tar.xz https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz \
    && tar -xJf gnu_gcc_arm.tar.xz \
    && rm gnu_gcc_arm.tar.xz


# Extract the actual directory name from the download
RUN TOOLCHAIN_DIR=$(find /usr -maxdepth 1 -type d -name "arm-gnu-toolchain*" -print -quit) && \
    echo "Found toolchain at: ${TOOLCHAIN_DIR}" && \
    echo "export PATH=${TOOLCHAIN_DIR}/bin:\$PATH" >> /etc/profile.d/arm-toolchain.sh

# Set environment variables for the current build
ENV PATH /usr/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi/bin:$PATH


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
    "__bash_prompt" \ >> ~/.bashrc
