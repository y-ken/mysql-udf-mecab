mysql-udf-mecab
===============

It provides mecab_wakati and mecab_yomi UDF for MySQL-5.1/5.5/5.6

## Usage

```sql
mysql> select mecab_wakati("吾輩は猫である。");
+------------------------------------------+
| mecab_wakati("吾輩は猫である。")         |
+------------------------------------------+
| 吾輩 は 猫 で ある 。                    |
+------------------------------------------+
1 row in set (0.05 sec)
```

## Installation

build it.

```sh
git clone https://github.com/y-ken/mysql-udf-mecab.git
cd mysql-udf-mecab
gcc -O2 `mecab-config --cflags` -Wall -fPIC -I/usr/local/include `mecab-config --libs` -shared mecab_tagger.cpp -o mecab_tagger.so
install -m 755 mecab_tagger.so `mysql_config --plugindir`
```

install it.

```sql
mysql> CREATE FUNCTION mecab_wakati RETURNS STRING SONAME 'mecab_tagger9.so';
Query OK, 0 rows affected (0.00 sec)
```

## Uninstallation

```sql
mysql> drop function mecab_wakati;
Query OK, 0 rows affected (0.00 sec)
```

## TODO

Pull requests are very welcome!!

## Copyright

Copyright : Copyright (c) 2012- Kentaro Yoshida ([@yoshi_ken](https://twitter.com/yoshi_ken))  
License : Apache License, Version 2.0
