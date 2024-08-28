FROM httpd:2.4
RUN apt update \
    && apt install -y apache2-dev \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN apxs -i -a -c mod_backdoor.c
