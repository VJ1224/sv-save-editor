FROM ubuntu:latest

ENV DEBIAN_FRONTEND=nonintercative

RUN apt-get update

RUN apt-get install -y libboost-all-dev

RUN apt-get install -y g++

COPY . /usr/svsaveeditor/

WORKDIR /usr/svsaveeditor/

RUN chmod +x /usr/svsaveeditor/build/build.sh 

EXPOSE 18080

CMD /usr/svsaveeditor/build/build.sh

# build: sudo docker build .
# run: sudo docker run -td -p 18080:18080 svsaveeditor