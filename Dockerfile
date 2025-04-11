FROM php:8.4.5

RUN apt-get update && apt search php8 && apt-get install -y build-essential autoconf automake bison flex re2c gdb \
libtool make pkgconf valgrind git libxml2-dev libsqlite3-dev && rm -rf /var/lib/apt/lists/*

WORKDIR /root
RUN git clone https://github.com/php/php-src.git
WORKDIR /root/php-src
RUN git checkout php-8.4.5
RUN ./buildconf --force && ./configure --enable-debug --prefix=$HOME/php-bin/DEBUG --with-config-file-path=$HOME/php-bin/DEBUG/etc
RUN make -j4
RUN make install
RUN export PATH=~/php-bin/DEBUG/bin:$PATH

# RUN curl https://install.duckdb.org | sh

# Set environment variables.
ENV HOME=/root

# Define working directory.
WORKDIR /ext

# Define default command.
CMD ["bash"]
