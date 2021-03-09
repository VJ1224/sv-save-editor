FROM ubuntu:latest

ENV DEBIAN_FRONTEND=nonintercative

RUN apt-get update

RUN apt-get install -y libboost-all-dev

RUN apt-get install -y g++

COPY . /usr/svsaveeditor/

WORKDIR /usr/svsaveeditor/

RUN chmod +x /usr/svsaveeditor/build/build.sh 

EXPOSE 18080

CMD /usr/svsaveeditor/build/build.sh && tail -f /dev/null

# build: sudo docker build --rm -t svsaveeditor:latest .
# run: sudo docker run --rm -p 18080:18080 svsaveeditor