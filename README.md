# Minitalk
What is MINITALK ??
二つの異なるプログラム間でプロセス通信を行う。
`server`プログラムと`client`プログラムを起動して、`client`に`SERVER_PID`と`serverに送信したい文字列`を引数として与えると、`server`が受け取った文字列を出力する。

## USAGE
```bash
$ git clone https://github.com/public-jun/minitalk.git
$ cd minitalk
$ make
$ ./server
SERVER PID 

(another window)
$ ./client SERVER_PID STRING


(In SERVER)
$ STRING...


```
