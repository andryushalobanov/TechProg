FROM ubuntu:18.04

LABEL auth="Mikhailov_Konstantin_Maksimovich_221-352"

ENV TZ=Europe/Moscow  
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && \
    apt-get install -y qt5-default qtbase5-dev qt5-qmake build-essential 

RUN mkdir -p /TechPr_221-352-Mikhailov
WORKDIR /TechPr_221-352-Mikhailov
COPY . .
RUN qmake exam.pro && make

CMD ["./exam", "exam"]