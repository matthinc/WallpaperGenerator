FROM debian:stretch-20190708-slim

WORKDIR ~

COPY ./include include
COPY ./src src
COPY Makefile Makefile

RUN mkdir build

RUN apt-get update
RUN apt -y install gcc g++ make
RUN apt -y install graphicsmagick-libmagick-dev-compat

RUN make

CMD ["build/wallpaper","-t","solid","-c","#ff0000","-o","/tmp/wp.png"]