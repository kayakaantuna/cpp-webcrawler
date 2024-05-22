# Welcome to our WebCrawler

**OpenCrawl** is an innovative and fully open source web crawling solution designed to navigate and analyze the vast expanse of the internet efficiently and effectively. Built with modularity and scalability in mind, OpenCrawl is ideal for developers, researchers, and organizations looking to extract and process web data at scale.

## Table of Contents
- [Welcome to our WebCrawler](#welcome-to-our-webcrawler)
  - [Table of Contents](#table-of-contents)
  - [Resource](#resource)
  - [How to compile](#how-to-compile)

## Resource
- [C++ Web Scraping: Tutorial 2024](https://www.zenrows.com/blog/c-plus-plus-web-scraping#c-plus-plus-good-for-web-scraping)

## Dependencies

```console
sudo apt install curl libcurl4-openssl-dev libxml2-dev libxml2-doc default-jre
```

Selenium Grid (Version may change, 4.21.0 stable)
```console
weget https://github.com/SeleniumHQ/selenium/releases/download/selenium-4.21.0/selenium-server-4.21.0.jar
```

Selenium Grid Start code (Not sure at the momment, but leaving it here)
```console
java -jar selenium-server-4.21.0.jar -port 4444 &
```

## How to compile

```console
mkdir build && cd build
cmake ..
sudo make && sudo make install
```

