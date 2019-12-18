FROM alpine:latest

LABEL maintainer="Weidong Lian <weidong.lian@gmail.com>"

WORKDIR "/project"

RUN apk update && \
    apk upgrade && \
    apk --update add \
        linux-headers \
        gcc \
        g++ \
        build-base \
        cmake \
        bash \
        libstdc++ \
        cppcheck \
        py-pip && \
        pip install conan && \
    rm -rf /var/cache/apk/*
