# geqo
Genetic Query Optimizer isolated from PostgreSQL

To install the extension in your database

```
make
sudo make install
```

Then in psql:

```
BEGIN;

LOAD 'geqo_extension';
SET geqo_threshold = 2;

CREATE TABLE test(
    TEXT col_1,
    TEXT col_2,
);

SELECT * FROM 
    test t1,
    test t2,
    test t3;

ROLLBACK;
```
