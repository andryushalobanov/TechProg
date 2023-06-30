FROM ubuntu:18.04

LABEL author="Mikhailov Konstantin 221-352"

ENV TZ=Europe/Moscow  
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone  
RUN apt-get update  
RUN apt-get install qt5-default -y  
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake  
RUN apt-get install build-essential -y 

WORKDIR /root/
RUN mkdir Mikhailov
WORKDIR /root/Mikhailov/

COPY *.cpp /root/Mikhailov/
COPY *.h /root/Mikhailov/
COPY *.pro /root/Mikhailov/

RUN qmake -o myshop echoServer_351.pro 
RUN make myshop

EXPOSE 44444