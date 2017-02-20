FROM gcc:latest

RUN apt-get update && \
    apt-get install -y valgrind cmake

ENV CRITERION_VERSION v2.3.0-1
ENV CRITERION_DIR criterion-${CRITERION_VERSION}
ENV CRITERION_TARBALL ${CRITERION_DIR}.tar.bz2
ENV CRITERION_URL https://github.com/Snaipe/Criterion/releases/download/${CRITERION_VERSION}/${CRITERION_TARBALL}

RUN curl -OL ${CRITERION_URL} && \
    tar xfvj ${CRITERION_TARBALL} && \
    cd ${CRITERION_DIR} && \
    cmake -H. -Bbuild && \
    cmake --build build -- install

WORKDIR /build
ADD . /build
