create database if not exists sys_order;

use sys_order;

create table if not exists dish_table(
    id int primary key auto_increment comment '菜品id',
    name varchar(32) unique key not null comment '菜品名称',
    price int not null comment '菜品价格',
    atime datetime comment '添加时间'
    );

create table if not exists order_table(
    id int primary key auto_increment comment '订单id',
    or_dish varchar(255) not null comment '[1,2]',
    status int not null comment '0--未完成状态，完成状态',
    mtime datetime comment '修改时间'
    );

insert dish_table values(null, "红烧茄子", 2300, now()),
                        (null, "鱼香肉丝", 2400, now());

insert order_table values(null, "[1]", 0, now()),
                        (null, "[1, 2]", 0, now());
