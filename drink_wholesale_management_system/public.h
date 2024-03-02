#ifndef DRINK_WHOLESALE_MANAGEMENT_SYSTEM_PUBLIC_H
#define DRINK_WHOLESALE_MANAGEMENT_SYSTEM_PUBLIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MaxSize 1005

/*定义所需结构体*/
///管理员信息
typedef struct Manager {
    char ID[9];//管理员账号
    char password[21];//管理员密码
    char Tel[12];//管理员电话
    float fund;//运行资金
}Manager;
///客户信息
typedef struct User {
    char ID[9];//客户账号
    char password[21];//客户密码
    char name[41];//营业网点名称
    int level;//客户级别
    char address[61];//客户地址
    char Tel[12];//客户联系方式
    float total_funding;//账户余额(单位：元)
    float total_consumption;//总消费(单位：元)
    struct User* next;
}User;
///酒水信息
typedef struct Drink {
    char ID[11];//酒水编号
    char brand[21];//酒水品牌
    char taste[21];//酒水口味
    int package;//包装种类(1、瓶装 2、罐装 3、盒装)
    char single_bottle_capacity[5];//单瓶容量(单位：mL)
    char single_box_quantity[3];//单箱数量(单位：瓶/罐)
    float restocking_price;//进货价格(单位：元)
    float sale_price;//销售价格(单位：元)
    int stock_quantity;//库存数量(单位：箱)
    struct Activity {//优惠活动
        int form;//优惠形式(0、无 1、折扣 2、赠品)
        float specific_1;//具体折扣
        int specific_2[2];//具体赠品
        char reason[20];//优惠原因
        char date[2][20];//活动开始时间和结束时间
    }activity;
    struct Drink* next;
}Drink;
///批发记录
typedef struct WholesaleRecord {
    char order_number[11];//订单编号
    char date[20];//订单日期(下单时间)
    char user_ID[9];//客户账号
    struct PastDrink {//酒水信息
        char ID[11];//酒水编号
        char brand[21];//酒水品牌
        char taste[21];//酒水口味
        int package;//包装种类(1、瓶装 2、罐装 3、盒装)
        char single_bottle_capacity[5];//单瓶容量(单位：mL)
        char single_box_quantity[3];//单箱数量(单位：瓶/罐)
        float sale_price;//销售价格(单位：元/箱)
    }past_drink;
    int goods_quantity;//批发数量(单位：箱)
    struct Discount {//优惠
        int form;//优惠形式(0、无 1、折扣 2、赠品)
        float specific_1;//具体折扣
        int specific_2[2];//具体赠品
        char reason[21];//优惠原因
    }discount[3];
    int goods_situation;//订单现况(0:未下单 1:已下单 2:派送中 3:已到货 4:申请退货 5:已退货)
    struct WholesaleRecord* next;
}WholesaleRecord;
///进货记录
typedef struct PurchaseRecord {
    char order_number[11];//订单编号
    char date[20];//订单日期(入库时间)
    char drink_ID[11];//酒水编号
    char brand[21];//酒水品牌
    char taste[21];//酒水口味
    int package;//包装种类(1、瓶装 2、罐装)
    char single_bottle_capacity[5];//单瓶容量(单位：mL)
    char single_box_quantity[3];//单箱数量(单位：瓶/罐)
    float restocking_price;//进货价格(单位：元/箱)
    int goods_quantity;//进货数量(单位：箱)
    struct PurchaseRecord* next;
}PurchaseRecord;



/*通用函数*/

///系统初始化
//创建管理员记录
Manager* CreatManager();
//创建用户链表
User* CreatUserList();
//创建酒水链表
Drink* CreatDrinkList();
//创建批发记录链表
WholesaleRecord* CreatWholesaleRecordList();
//创建进货记录链表
PurchaseRecord* CreatPurchaseRecordList();

///更新文件
//更新管理员文件
void RenewManagerFile();
//更新用户文件
void RenewUserFile();
//更新酒水文件
void RenewDrinkFile();
//更新批发记录文件
void RenewWholesaleRecordFile();
//更新进货记录文件
void RenewPurchaseRecordFile();

///检验信息
//检验输入信息是否正确
bool isInputCorrect(char* correct_string, char* input);
//检验密码是否符合规范
bool isPasswordAllowed(char* password);
//检验数字串（联系方式或金额）是否符合规范
bool isNumberAllowed(char* number);
//检验字符串（地址或名称）是否符合规范
bool isStringAllowed(char* string);
//检验时间格式是否正确
bool isTimeAllowed(char* time);
//检验时间顺序是否正确
bool isChronological(char* early_time, char* late_time);
//模糊查找
bool isInclude(char* string, char* input);
//用户是否存在
User* isUserExist(char* input);
//酒水是否存在（返回前驱结点）
Drink* isDrinkExist(char* drink_ID);
//订单是否存在（返回前驱结点）
WholesaleRecord* isOrderExist();
//生成编号
char* BuildID(char* pre_ID);
///输入信息
//输入订单现状
int isSituationCorrect(char* situation);
//输入品牌
int isBrandCorrect(char* brand);
//输入口味
int isTasteCorrect(char* taste);
//输入包装
int isPackageCorrect(char* package, int type);
//输入单瓶容量
int isSingleBottleCapacityCorrect(char* single_bottle_capacity);
//输入单箱数量
int isSingleBoxQuantityCorrect(char* single_box_quantity);
//输入价格
int isPriceCorrect(char* price);
//输入箱数
int isGoodsQuantityCorrect(char* goods_quantity);
//输入折扣
int isDiscountCorrect(char* discount);
//输入活动原因
int isReasonCorrect(char* reason);
//确认输入
int isSure();

#endif //DRINK_WHOLESALE_MANAGEMENT_SYSTEM_PUBLIC_H
