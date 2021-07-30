#include<iostream>
#include<unistd.h>
using namespace std;
#include<jsoncpp/json/json.h>
#include<mysql/mysql.h>
#include<mutex>

#define HOST "127.0.0.1"
#define ROOT "root"
#define PASSWD ""
#define DB "sys_order"
namespace order_sys
{
  static MYSQL* MySqlInit()
  {
    //初始化操作句柄
    MYSQL *mysql = NULL;
    mysql = mysql_init(mysql);
    if(mysql == NULL)
    {
      cout << "mysql init error" << endl;
      return NULL;
    }

    //通过句柄连接mysql服务器
    // MYSQL* mysql_real_connect(初始化完成的句柄，连接的MySQL服务器的地址，连接的服务器的用户名，连接的服务器的密码，默认选择数据库的名称，连接的服务器的端口，socket文件， 客户端标志位)
    MYSQL *ret = mysql_real_connect(mysql, HOST, ROOT, PASSWD, DB, 0, NULL, 0);
    if(ret == NULL)
    {
      cout << "mysql connect failed" << endl;
      return NULL;
    }
    //设置客户端字符集
    int result = mysql_set_character_set(mysql, "utf8");
    if(result != 0)
    {
      cout << "mysql set character failed" << endl;
      return NULL;
    }
    //选择使用的数据库
    //因为前面已经选择过，所以这一步可以省略
    return mysql;
  } 

  static bool  MysqlQuery(MYSQL* mysql, const char* str)
  {
    int ret = mysql_query(mysql, str);
    if(ret != 0)
    {
      cout << "mysql query failed" << endl;
      cout << mysql_error(mysql) << endl;
      return false;
    }
    return true;
  }

  static void  MysqlRealse(MYSQL* mysql)
  {
    if(mysql)
    {
      mysql_close(mysql);
    }
  }


  class tb_dish
  {
    public:

      //构造函数
      tb_dish()
      {
       _mysql = MySqlInit();
       if(_mysql == NULL)
       {
         cout << "mysql init failed" << endl;
         exit(-1);
       }
      }

      bool Insert(const Json::Value& val)
      {
       #define DISH_Insert "insert dish_table values(null, '%s', %d, now());"
          char str_sql[4096] = {0};
          sprintf(str_sql, DISH_Insert, val["name"].asCString(), val["price"].asInt());
         
          bool result = MysqlQuery(_mysql, str_sql);
          if(result == false)
          {
             cout << "Insert failed" << endl;
             return false;
          }
          return true;
      }
      bool Delete(int dish_id)
      {
         #define DISH_DELETE "delete from dish_table where id=%d;"
         char str_delete[4096] = {0};
         sprintf(str_delete, DISH_DELETE, dish_id);
         bool ret = MysqlQuery(_mysql, str_delete);
         if(ret == false)
         {
           cout << "Delete failed" << endl;
           return false;
         }
         return true;
      }
      bool Update(const Json::Value& dish)
      {
        #define DISH_UPDATE "update dish_table set name='%s',price=%d  where id=%d;"
        char str_update[4096] = {0};
        sprintf(str_update, DISH_UPDATE, dish["name"].asCString(), dish["price"].asInt(), dish["id"].asInt());
        bool ret = MysqlQuery(_mysql, str_update);
        if(ret == false)
        {
          cout << "update failed" << endl;
          return false;
        }
        return true;
      }
     
      bool SelectAll(Json::Value& dishes)
      {
        const char *select = "select * from dish_table;";
        //执行语句
        //因为执行语句与获取查询结果存在线程安全，所以加上互斥锁
        _mutex.lock();
        bool ret = MysqlQuery(_mysql, select);
        if(ret == false)
        {
          cout << "SelectAll failed" << endl;
          _mutex.unlock();
          return false;
        }
        _mutex.unlock();
        //将查询结果获取到本地
        MYSQL_RES* result = mysql_store_result(_mysql);
        if(result == NULL)
        {
          cout << "mysql store result failed" << endl;
          return false;
        }
        //获取结果中数据的条数，列数
        int row = mysql_num_rows(result);
        //遍历结果集获取每一条数据的每一列
        for(int i = 0; i < row; i++)
        {
          MYSQL_ROW res = mysql_fetch_row(result);
          Json::Value dish;
          dish["id"] = stoi(res[0]);
          dish["name"] = res[1];
          dish["price"] = stoi(res[2]);
          dish["atime"] = res[3];

          dishes.append(dish);
        }
        //释放本地结果集
        mysql_free_result(result);
        return true;
      }
      bool SelectOne(int dish_id, Json::Value& dish)
      {
        #define SELECTONE "select * from dish_table where id=%d;"
        char str_select[4096] = {0};
        sprintf(str_select, SELECTONE, dish_id);
        //执行语句
        _mutex.lock();
        bool ret = MysqlQuery(_mysql, str_select);
        if(ret == false)
        {
          cout << "selectone failed";
          _mutex.unlock();
          return false;
        }
        _mutex.unlock();
        //获取结果集
        MYSQL_RES* result = mysql_store_result(_mysql);
        if(result == NULL)
        {
          cout << "selectone store result failed" << endl;
          return false;
        }
        //获取行数
        int row = mysql_num_rows(result);
        if(row != 1)
        {
          cout << "mysql_num_rows failed" << endl; 
          cout << "please check dish_id:" << dish_id << " is already exist" << endl;
          return false;
        }
        //遍历结果集
        MYSQL_ROW res = mysql_fetch_row(result);
        dish["id"] = stoi(res[0]);
        dish["name"] = res[1];
        dish["price"] = stoi(res[2]);
        dish["atime"] = res[3];
        //释放结果集
        mysql_free_result(result);
        return true;
      }

      ~tb_dish()
      {
        if(_mysql)
        {
          MysqlRealse(_mysql);
          _mysql = NULL;
        }

      }

    private:
      MYSQL *_mysql;
      mutex _mutex;
  };

  class order_dish
  {
    public:
      order_dish()
      {
        _mysql = MySqlInit();
        if(_mysql == NULL)
        {
          cout << "order dish init failed" << endl;
          exit(-1);
        }
      }
      bool Insert(const Json::Value order)
      {
        #define INSERT "Insert order_table values(null, '%s', 0, now());"
        Json::FastWriter writer;
        string str = writer.write(order["or_dish"]);
        char str_insert[4096] = {0};
        str[str.size() - 1] = '\0';
        sprintf(str_insert, INSERT, str.c_str());
        bool ret = MysqlQuery(_mysql, str_insert);
        if(ret == false)
        {
          cout << "order insert failed" << endl;
          return false;
        }
        return true;
      }

      bool Delete(int order_id)
      {
        #define DELETEORD "delete from order_table where id=%d;"
        char str_delete[4096] = {0};
        sprintf(str_delete, DELETEORD, order_id);
        bool ret = MysqlQuery(_mysql, str_delete);
        if(ret == false)
        {
          cout << "order delete failed" << endl;
          return false;
        }
        return true;
      }

      bool Update(const Json::Value ord)
      {
       #define UPDATE "update order_table set or_dish='%s',status=%d,mtime=now() where id=%d;"
       char str_update[4096] = {0};
       Json::FastWriter writer;
       string str = writer.write(ord["or_dish"]);
       str[str.size() - 1] = '\0';
       sprintf(str_update, UPDATE, str.c_str(), ord["status"].asInt(), ord["id"].asInt());
       bool ret = MysqlQuery(_mysql, str_update);
       if(ret == false)
       {
         cout << "order update failed" << endl;
         return false;
       }
       return true;
      }
      bool SelectAll(Json::Value& orders)
      {
        const char* str_selectAll = "select * from order_table;";
        //执行语句
        _mutex.lock();
        bool ret = MysqlQuery(_mysql, str_selectAll);
        if(ret == false)
        {
          cout << "order select all failed" << endl;
          _mutex.unlock();
          return false;
        }
        _mutex.unlock();
        //获取结果集
        MYSQL_RES* result = mysql_store_result(_mysql);
        if(result == NULL)
        {
          cout << "order mysql store result failed" << endl;
          return false;
        }
        //获取行数
        int row = mysql_num_rows(result);
        //遍历结果集
        for(int i = 0; i < row; i++)
        {
          Json::Value order;
          MYSQL_ROW res = mysql_fetch_row(result);
          order["id"] = stoi(res[0]);
          Json::Reader reader;
          reader.parse(res[1],order["or_dish"]);
          order["status"] = stoi(res[2]);
          order["mtime"] = res[3];
          orders.append(order);
        }
        //释放结果集
        mysql_free_result(result);
        return true;
      }
      bool SelectOne(int order_id, Json::Value& order)
      {
        #define ORDERSELECTONE "select * from order_table where id=%d;"
        char str_selectOne[4096] = {0};
        sprintf(str_selectOne, ORDERSELECTONE, order_id);
        //执行语句
        _mutex.lock();
        bool ret = MysqlQuery(_mysql, str_selectOne);
        if(ret == false)
        {
          cout << "order mysqlquery failed";
          _mutex.unlock();
          return false;
        }
        _mutex.unlock();
        //获取结果集
        MYSQL_RES* result = mysql_store_result(_mysql);
        if(result == NULL)
        {
          cout << "order mysql store result  failed" << endl;
          return false;
        }
        //获取行数
        int row = mysql_num_rows(result);
        if(row != 1)
        {
          cout << "order mysql_num_rows failed";
          return false;
        }
        //遍历结果集
        MYSQL_ROW res = mysql_fetch_row(result);
        order["id"] = stoi(res[0]);
        Json::Reader reader;
        reader.parse(res[1], order["or_dish"]);
        order["status"] = stoi(res[2]);
        order["ctime"] = res[3];
        //释放结果集
        mysql_free_result(result);
        return true;
      }

      ~order_dish()
      {
        if(_mysql)
        {
          MysqlRealse(_mysql);
          _mysql = NULL;
        }
      }

    private:
      MYSQL *_mysql;
      mutex _mutex;
  };
}
