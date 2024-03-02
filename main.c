#include "public.h"
#include "manager.h"
#include "user.h"

//创建管理员记录
Manager *manager;
//创建用户链表
User *user_head;
//创建酒水链表
Drink *drink_head;
//创建批发记录链表
WholesaleRecord *wholesaleRecord_head;
//创建进货记录链表
PurchaseRecord *purchaseRecord_head;

/*** 初始页面 ***/
//系统初始化
void SystemInitialization();

//登录页面
void LoginMenu();
/*** 用户页面 ***/
///用户登录页面
void UserLoginMenu();

///用户功能页面
void UserMenu(User *user);

//用户个人信息页面
void UserInformationMenu(User *user);

//用户信息修改页面
void UserModifyInformationMenu(User *user);

//查看酒水页面
void UserViewAvailableDrinksMenu(User *user);

//用户购物车页面
void UserViewShoppingCartMenu(User *user);

//用户批发记录页面
void UserViewWholesaleRecordMenu(User *user);
/*** 管理员页面 ***/
///管理员登录页面
void ManagerLoginMenu();

///管理员功能页面
void ManagerMenu();

//管理员信息页面
void ManagerInformationMenu();

//用户信息页面
void UsersInformationMenu();

//查找用户页面
void SearchUserMenu();

//查看酒水页面
void ManagerViewAvailableDrinksMenu();

//修改酒水信息页面
void ModifyDrinkInformationMenu(Drink *found_drink_head);

//管理员查看最新消息页面
void ManagerViewNewMessageMenu();

//查看下单信息页面
void ManagerViewOrderInformationMenu();

//查看退单信息页面
void ManagerViewReturnInformationMenu();

//管理员批发记录页面
void ManagerViewWholesaleRecordMenu();

//管理员进货记录页面
void ManagerViewPurchaseRecordMenu();

//管理员进货记录修改页面
void ManagerModifyPurchaseRecordMenu(PurchaseRecord *head);

int main(void) {
    SystemInitialization();
    LoginMenu();
    return 0;
}

/*** 初始页面 ***/
//系统初始化
void SystemInitialization() {
    manager = CreatManager();
    user_head = CreatUserList();
    drink_head = CreatDrinkList();
    wholesaleRecord_head = CreatWholesaleRecordList();
    purchaseRecord_head = CreatPurchaseRecordList();
}

//登录页面
void LoginMenu() {
    while (true) {
        system("cls");
        printf("欢迎进入酒水批发系统！\n");
        printf("*****************************\n");
        printf("********1、管理员登录********\n");
        printf("********2、客户登录**********\n");
        printf("********0、退出系统**********\n");
        printf("*****************************\n");
        printf("您的选择是：");
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //选择管理员身份登录
        if (select[0] == '1' && strlen(select) == 2) { ManagerLoginMenu(); }
            //选择用户身份登录
        else if (select[0] == '2' && strlen(select) == 2) { UserLoginMenu(); }
            //退出系统
        else if (select[0] == '0' && strlen(select) == 2) { return; }
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}
/*** 用户页面 ***/
///用户登录页面
void UserLoginMenu() {
    while (true) {
        system("cls");
        printf("欢迎进入客户模式！\n");
        printf("***************************\n");
        printf("*********1、登录***********\n");
        printf("*********2、注册***********\n");
        printf("*********3、忘记密码*******\n");
        printf("*********0、返回***********\n");
        printf("***************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //选择登录账号
        if (select[0] == '1' && strlen(select) == 2) {
            User *user = UserLogin(user_head);
            //登录成功，进入用户功能页面
            if (user) { UserMenu(user); }
        }
            //选择注册账号
        else if (select[0] == '2' && strlen(select) == 2) { UserSignUp(); }
            //选择忘记密码
        else if (select[0] == '3' && strlen(select) == 2) { ForgotUserPassword(); }
            //选择返回
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

///用户功能页面
void UserMenu(User *user) {
    while (true) {
        //功能选择页面
        system("cls");
        printf("*******************************\n");
        printf("********1、查看个人信息********\n");
        printf("********2、查看在售酒水********\n");
        printf("********3、查看购物车**********\n");
        printf("********4、查看订单************\n");
        printf("********0、退出登录************\n");
        printf("*******************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //查看个人信息
        if (select[0] == '1' && strlen(select) == 2) { UserInformationMenu(user); }
            //查看在售酒水
        else if (select[0] == '2' && strlen(select) == 2) { UserViewAvailableDrinksMenu(user); }
            //查看购物车
        else if (select[0] == '3' && strlen(select) == 2) { UserViewShoppingCartMenu(user); }
            //查看批发记录
        else if (select[0] == '4' && strlen(select) == 2) { UserViewWholesaleRecordMenu(user); }
            //退出登录
        else if (select[0] == '0' && strlen(select) == 2) {
            printf("退出成功，欢迎下次使用！\n");
            system("read");
            return;
        }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//用户个人信息页面
void UserInformationMenu(User *user) {
    while (true) {
        //用户查看个人信息
        system("cls");
        UserInformation(user, 1);
        //相关操作
        printf("\n操作\n");
        printf("***************************\n");
        printf("********1、修改信息********\n");
        printf("********2、修改密码********\n");
        printf("********3、充值余额********\n");
        printf("********0、退出界面********\n");
        printf("***************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //选择修改的信息
        if (select[0] == '1' && strlen(select) == 2) { UserModifyInformationMenu(user); }
            //修改密码
        else if (select[0] == '2' && strlen(select) == 2) { ModifyUserPassword(user); }
            //充值余额
        else if (select[0] == '3' && strlen(select) == 2) { UserRecharge(user); }
            //退出个人信息界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//用户信息修改页面
void UserModifyInformationMenu(User *user) {
    while (true) {
        //用户可修改信息
        system("cls");
        printf("********************************\n");
        printf("***** 1、网点名称：%s\n", user->name);
        printf("***** 2、收货地址：%s\n", user->address);
        printf("***** 3、联系方式：%s\n", user->Tel);
        printf("***** 0、返回个人信息界面\n");
        printf("********************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //修改网点名称
        if (select[0] == '1' && strlen(select) == 2) { ModifyUserName(user); }
            //修改网点地址
        else if (select[0] == '2' && strlen(select) == 2) { ModifyUserAddress(user); }
            //修改联系方式
        else if (select[0] == '3' && strlen(select) == 2) { ModifyUserTel(user); }
            //返回个人信息界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//查看酒水页面
void UserViewAvailableDrinksMenu(User *user) {
    char brand[MaxSize] = {""};
    char taste[MaxSize] = {""};
    char package[MaxSize] = {""};
    char capacity[MaxSize] = {""};
    char activity[MaxSize] = {""};
    Drink *found_drink_head = NULL;    //创建查询酒水链表
    while (true) {
        //界面
        system("cls");
        if (!found_drink_head) {
            //用户查看全部在售酒水
            ViewAvailableDrinks(found_drink_head, 1, 0);
            //相关操作
            printf("\n操作\n");
            printf("*********************************\n");
            printf("******1、选择酒水加入购物车******\n");
            printf("******2、选择酒水直接下单********\n");
            printf("******3、按条件搜索酒水**********\n");
            printf("******0、退出酒水界面************\n");
            printf("*********************************\n");
            printf("您的选择是：");
        } else {
            //用户查看搜索到的在售酒水
            printf("搜索条件\n");
            printf("**************************************\n");
            printf("品牌：%s\n", brand);
            printf("口味：%s\n", taste);
            printf("包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]);
            printf("单瓶容量：%smL\n", capacity);
            printf("优惠活动(1折扣，2赠品，3不限)：%c\n", activity[0]);
            printf("**************************************\n");
            ViewAvailableDrinks(found_drink_head, 1, 0);
            //相关操作
            printf("\n操作\n");
            printf("*********************************\n");
            printf("******1、选择酒水加入购物车******\n");
            printf("******2、选择酒水直接下单********\n");
            printf("******3、按条件搜索酒水**********\n");
            printf("******0、退出搜索界面************\n");
            printf("*********************************\n");
            printf("您的选择是：");
        }
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //选择酒水加入购物车
        if (select[0] == '1' && strlen(select) == 2) { AddDrinkToTheCart(user, found_drink_head); }
            //选择酒水直接下单
        else if (select[0] == '2' && strlen(select) == 2) { PayForDrink(user, found_drink_head); }
            //按条件搜索酒水操作页面
        else if (select[0] == '3' && strlen(select) == 2) {
            //销毁查询酒水链表
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
            //输入查询条件
            if (InputDrinkConditions(brand, taste, package, capacity, activity) == 1) {
                //建立查询酒水链表
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //返回上一界面
        else if (select[0] == '0' && strlen(select) == 2) {
            if (!found_drink_head) { return; }
            else {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
        }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//用户购物车页面
void UserViewShoppingCartMenu(User *user) {
    while (true) {
        //创建购物车链表
        WholesaleRecord *cart_head = CreatUserShoppingCartList(user);
        //查看用户购物车
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        printf("\n操作\n");
        printf("*******************************\n");
        printf("********1、修改订单************\n");
        printf("********2、选择订单下单********\n");
        printf("********3、全选下单************\n");
        printf("********4、选择订单删除********\n");
        printf("********5、清空购物车**********\n");
        printf("********0、退出购物车**********\n");
        printf("*******************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //修改订单
        if (select[0] == '1' && strlen(select) == 2) { UserModifyAnOrder(user, cart_head); }
            //选择订单下单
        else if (select[0] == '2' && strlen(select) == 2) { PayForAnOrder(user, cart_head); }
            //全选下单
        else if (select[0] == '3' && strlen(select) == 2) { PayForAllOrder(user, cart_head); }
            //选择订单删除
        else if (select[0] == '4' && strlen(select) == 2) { DeleteAnOrder(user, cart_head); }
            //清空购物车
        else if (select[0] == '5' && strlen(select) == 2) { clsShoppingCart(user, cart_head); }
            //退出购物车
        else if (select[0] == '0' && strlen(select) == 2) {
            //销毁用户购物车链表
            DestroyTempWholesaleRecordList(cart_head);
            cart_head = NULL;
            return;
        }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
        //销毁用户购物车链表
        DestroyTempWholesaleRecordList(cart_head);
        cart_head = NULL;
    }
}

//用户批发记录页面
void UserViewWholesaleRecordMenu(User *user) {
    char date[MaxSize] = {""};
    char situation[MaxSize] = {""};
    char brand[MaxSize] = {""};
    char taste[MaxSize] = {""};
    char package[MaxSize] = {""};
    char capacity[MaxSize] = {""};
    WholesaleRecord *found_wholesaleRecord_head = NULL;    //创建查询批发记录链表
    while (true) {
        system("cls");
        if (!found_wholesaleRecord_head) {
            //用户查看所有的批发记录
            ViewWholesaleRecords(found_wholesaleRecord_head, user, 6, 0);
            //相关操作
            printf("\n操作\n");
            printf("*******************************\n");
            printf("********1、申请退货************\n");
            printf("********2、查找订单************\n");
            printf("********0、退出页面************\n");
            printf("*******************************\n");
            printf("您的选择是：");
        } else {
            //用户查看搜索到的批发记录
            printf("搜索条件\n");
            printf("**************************************\n");
            printf("订单日期：%s\n", date);
            printf("订单现况(1已下单，2派送中，3已到货，4申请退货，5已退货，6不限)：%c\n", situation[0]);
            printf("品牌：%s\n", brand);
            printf("口味：%s\n", taste);
            printf("包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]);
            printf("单瓶容量：%sml\n", capacity);
            printf("**************************************\n");
            ViewWholesaleRecords(found_wholesaleRecord_head, user, 6, 0);
            //相关操作
            printf("\n操作\n");
            printf("*******************************\n");
            printf("********1、申请退货************\n");
            printf("********2、查找订单************\n");
            printf("********0、退出搜索页面********\n");
            printf("*******************************\n");
            printf("您的选择是：");
        }
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //申请退货
        if (select[0] == '1' && strlen(select) == 2) { UserApplicationForReturn(user, found_wholesaleRecord_head); }
            //查找订单
        else if (select[0] == '2' && strlen(select) == 2) {
            //销毁查询批发记录链表
            if (found_wholesaleRecord_head) {
                DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                found_wholesaleRecord_head = NULL;
            }
            //输入查询条件
            if (UserInputWholesaleRecordConditions(date, situation, brand, taste, package, capacity) == 1) {
                //建立查询批发记录链表
                found_wholesaleRecord_head = CreatUserFoundWholesaleRecordList(date, situation, brand, taste, package,
                                                                               capacity);
            }
        }
            //返回上一界面
        else if (select[0] == '0' && strlen(select) == 2) {
            if (!found_wholesaleRecord_head) { return; }
            else {
                DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                found_wholesaleRecord_head = NULL;
            }
        }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}
/*** 管理员页面 ***/
///管理员登录页面
void ManagerLoginMenu() {
    while (true) {
        system("cls");
        printf("欢迎进入管理员模式！\n");
        printf("***************************\n");
        printf("*********1、登录***********\n");
        printf("*********2、忘记密码*******\n");
        printf("*********0、返回***********\n");
        printf("***************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //选择登录账号
        if (select[0] == '1' && strlen(select) == 2) {
            //登录成功，进入管理员功能页面
            if (ManagerLogin()) { ManagerMenu(); }
        }
            //选择忘记密码
        else if (select[0] == '2' && strlen(select) == 2) { ForgotManagerPassword(); }
            //选择返回
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

///管理员功能页面
void ManagerMenu() {
    while (true) {
        //功能选择页面
        system("cls");
        printf("*******************************\n");
        printf("********1、查看管理员信息******\n");
        printf("********2、查看用户信息********\n");
        printf("********3、查看在售酒水********\n");
        printf("********4、查看最新消息********\n");
        printf("********5、查看批发订单********\n");
        printf("********6、查看进货订单********\n");
        printf("********0、退出登录************\n");
        printf("*******************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //查看管理员信息
        if (select[0] == '1' && strlen(select) == 2) { ManagerInformationMenu(); }
            //查看用户信息
        else if (select[0] == '2' && strlen(select) == 2) { UsersInformationMenu(); }
            //查看在售酒水
        else if (select[0] == '3' && strlen(select) == 2) { ManagerViewAvailableDrinksMenu(); }
            //查看最新消息
        else if (select[0] == '4' && strlen(select) == 2) { ManagerViewNewMessageMenu(); }
            //查看批发记录
        else if (select[0] == '5' && strlen(select) == 2) { ManagerViewWholesaleRecordMenu(); }
            //查看进货记录
        else if (select[0] == '6' && strlen(select) == 2) { ManagerViewPurchaseRecordMenu(); }
            //退出登录
        else if (select[0] == '0' && strlen(select) == 2) {
            printf("退出成功，欢迎下次使用！\n");
            system("read");
            return;
        }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//管理员信息页面
void ManagerInformationMenu() {
    while (true) {
        //查看管理员信息
        system("cls");
        ManagerInformation();
        //相关操作
        printf("\n操作\n");
        printf("***************************\n");
        printf("*******1、修改联系方式*****\n");
        printf("*******2、修改密码*********\n");
        printf("*******0、退出界面*********\n");
        printf("***************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //修改联系方式
        if (select[0] == '1' && strlen(select) == 2) { ModifyManagerTel(); }
            //修改密码
        else if (select[0] == '2' && strlen(select) == 2) { ModifyManagerPassword(); }
            //退出管理员信息界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//用户信息页面
void UsersInformationMenu() {
    while (true) {
        system("cls");
        UserInformation(NULL, 0);
        //相关操作
        printf("\n操作\n");
        printf("***************************\n");
        printf("********1、查找用户********\n");
        printf("********0、退出界面********\n");
        printf("***************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //查找用户
        if (select[0] == '1' && strlen(select) == 2) { SearchUserMenu(); }
            //退出界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//查找用户页面
void SearchUserMenu() {
    //查找账号
    User *user = NULL;
    while (true) {
        system("cls");
        //输入账号或联系方式
        printf("请输入账号或联系方式(输入0返回)：");
        char input[MaxSize] = {""};
        fgets(input, sizeof(input), stdin);
        //检测是否返回
        if (input[0] == '0' && strlen(input) == 2) { return; }
        //检测用户是否存在
        user = isUserExist(input);
        if (!user) {
            printf("用户不存在，请重新输入！\n");
            system("read");
        } else { break; }
    }
    //操作账号
    while (true) {
        system("cls");
        UserInformation(user, 0);
        //相关操作
        printf("\n操作\n");
        printf("***************************\n");
        printf("*******1、重置密码*********\n");
        printf("*******0、退出界面*********\n");
        printf("***************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //重置用户密码
        if (select[0] == '1' && strlen(select) == 2) { ResetUserPassword(user); }
            //退出界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//查看酒水页面
void ManagerViewAvailableDrinksMenu() {
    char brand[MaxSize] = {""};
    char taste[MaxSize] = {""};
    char package[MaxSize] = {""};
    char capacity[MaxSize] = {""};
    char activity[MaxSize] = {""};
    Drink *found_drink_head = NULL;    //创建查询酒水链表
    while (true) {
        //界面
        system("cls");
        if (!found_drink_head) {
            //管理员查看全部在售酒水
            ViewAvailableDrinks(found_drink_head, 0, 0);
            //相关操作
            printf("\n操作\n");
            printf("*********************************\n");
            printf("********1、修改酒水信息**********\n");
            printf("********2、设置优惠活动**********\n");
            printf("********3、按条件搜索酒水********\n");
            //printf("********4、按销量排序************\n");
            printf("********4、下架酒水**************\n");
            printf("********0、退出酒水界面**********\n");
            printf("*********************************\n");
            printf("您的选择是：");
        } else {
            //管理员查看搜索到的在售酒水
            printf("搜索条件\n");
            printf("**************************************\n");
            printf("品牌：%s\n", brand);
            printf("口味：%s\n", taste);
            printf("包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]);
            printf("单瓶容量：%smL\n", capacity);
            printf("优惠活动(1折扣，2赠品，3不限)：%c\n", activity[0]);
            printf("**************************************\n");
            ViewAvailableDrinks(found_drink_head, 0, 0);
            //相关操作
            printf("\n操作\n");
            printf("*********************************\n");
            printf("********1、修改酒水信息**********\n");
            printf("********2、设置优惠活动**********\n");
            printf("********3、按条件搜索酒水********\n");
            printf("********4、下架酒水**************\n");
            //printf("********4、按销量排序************\n");
            printf("********0、退出搜索界面**********\n");
            printf("*********************************\n");
            printf("您的选择是：");
        }
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //修改酒水信息
        if (select[0] == '1' && strlen(select) == 2) {
            ModifyDrinkInformationMenu(found_drink_head);
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //设置优惠活动
        else if (select[0] == '2' && strlen(select) == 2) {
            SetActivity(found_drink_head, 0);
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //按条件搜索酒水操作页面
        else if (select[0] == '3' && strlen(select) == 2) {
            //销毁查询酒水链表
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
            //输入查询条件
            if (InputDrinkConditions(brand, taste, package, capacity, activity) == 1) {
                //建立查询酒水链表
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //下架酒水
        else if (select[0] == '4' && strlen(select) == 2) {
            TakeDownDrink(found_drink_head, 0);
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
        }
            //返回上一界面
        else if (select[0] == '0' && strlen(select) == 2) {
            //退出酒水界面
            if (!found_drink_head) { return; }
                //退出酒水搜索界面
            else {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
        }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//修改酒水信息页面
void ModifyDrinkInformationMenu(Drink *found_drink_head) {
    //查找要修改的酒水
    Drink *drink = NULL;
    while (true) {
        system("cls");
        ViewAvailableDrinks(found_drink_head, 0, 0);
        printf("请输入要修改酒水编号(输入0返回)：");
        char drink_ID[MaxSize] = {""};
        fgets(drink_ID, sizeof(drink_ID), stdin);
        //检验是否返回
        if (drink_ID[0] == '0' && strlen(drink_ID) == 2) { return; }
        //检验酒水是否存在
        drink = isDrinkExist(drink_ID);
        if (!drink->next) {
            printf("未找到酒水，请重新输入！\n");
            system("read");
        } else { break; }
    }
    //修改酒水信息
    while (true) {
        system("cls");
        ViewAvailableDrinks(drink, 0, 1);
        printf("\n操作\n");
        printf("*********************************\n");
        printf("*********1、修改销售价格*********\n");
        printf("*********2、设置优惠活动*********\n");
        printf("*********3、下架*****************\n");
        printf("*********0、退出修改界面*********\n");
        printf("*********************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //修改销售价格
        if (select[0] == '1' && strlen(select) == 2) { ModifyDrinkSalePrice(drink); }
            //设置优惠活动
        else if (select[0] == '2' && strlen(select) == 2) { SetActivity(drink, 1); }
            //下架酒水
        else if (select[0] == '3' && strlen(select) == 2) {
            TakeDownDrink(drink, 1);
            return;
        }
            //退出界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//管理员查看最新消息页面
void ManagerViewNewMessageMenu() {
    while (true) {
        system("cls");
        printf("*******************************\n");
        printf("**********1、下单信息**********\n");
        printf("**********2、退货信息**********\n");
        printf("**********0、退出界面**********\n");
        printf("*******************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //下单信息
        if (select[0] == '1' && strlen(select) == 2) { ManagerViewOrderInformationMenu(); }
            //退货信息
        else if (select[0] == '2' && strlen(select) == 2) { ManagerViewReturnInformationMenu(); }
            //退出界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//查看下单信息页面
void ManagerViewOrderInformationMenu() {
    while (true) {
        system("cls");
        ViewWholesaleRecords(NULL, NULL, 1, 0);
        printf("\n操作\n");
        printf("*******************************\n");
        printf("**********1、接受下单**********\n");
        printf("**********0、退出界面**********\n");
        printf("*******************************\n");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //接受下单
        if (select[0] == '1' && strlen(select) == 2) { AcceptOrder(); }
            //退出界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//查看退单信息页面
void ManagerViewReturnInformationMenu() {
    while (true) {
        system("cls");
        ViewWholesaleRecords(NULL, NULL, 4, 0);
        printf("\n操作\n");
        printf("*******************************\n");
        printf("**********1、接受退货**********\n");
        printf("**********0、退出界面**********\n");
        printf("*******************************\n");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //接受退货
        if (select[0] == '1' && strlen(select) == 2) { AcceptReturn(); }
            //退出界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}

//管理员批发记录页面
void ManagerViewWholesaleRecordMenu() {
    while (true) {
        char user[MaxSize] = {""};
        char date[MaxSize] = {""};
        char situation[MaxSize] = {""};
        char brand[MaxSize] = {""};
        char taste[MaxSize] = {""};
        char package[MaxSize] = {""};
        char capacity[MaxSize] = {""};
        WholesaleRecord *found_wholesaleRecord_head = NULL;    //创建查询批发记录链表
        while (true) {
            system("cls");
            if (!found_wholesaleRecord_head) {
                //管理员查看所有的批发记录
                ViewWholesaleRecords(found_wholesaleRecord_head, NULL, 6, 0);
                //相关操作
                printf("\n操作\n");
                printf("*********************************\n");
                printf("**********1、查找订单************\n");
                printf("**********2、修改订单************\n");
                printf("**********0、退出页面************\n");
                printf("*********************************\n");
                printf("您的选择是：");
            } else {
                //管理员查看搜索到的批发记录
                printf("搜索条件\n");
                printf("**************************************\n");
                printf("用户账号或联系方式：%s\n", user);
                printf("订单日期：%s\n", date);
                printf("订单现况(1已下单，2派送中，3已到货，4申请退货，5已退货，6不限)：%c\n", situation[0]);
                printf("品牌：%s\n", brand);
                printf("口味：%s\n", taste);
                printf("包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]);
                printf("单瓶容量：%sml\n", capacity);
                printf("**************************************\n");
                ViewWholesaleRecords(found_wholesaleRecord_head, NULL, 6, 0);
                //相关操作
                printf("\n操作\n");
                printf("*********************************\n");
                printf("**********1、查找订单************\n");
                printf("**********2、修改订单************\n");
                printf("**********0、退出搜索页面********\n");
                printf("*********************************\n");
                printf("您的选择是：");
            }
            //输入选择
            char select[MaxSize] = {""};
            fgets(select, sizeof(select), stdin);
            //查找订单
            if (select[0] == '1' && strlen(select) == 2) {
                //销毁查询批发记录链表
                if (found_wholesaleRecord_head) {
                    DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                    found_wholesaleRecord_head = NULL;
                }
                //输入查询条件
                if (ManagerInputWholesaleRecordConditions(user, date, situation, brand, taste, package, capacity) ==
                    1) {
                    //建立查询批发记录链表
                    found_wholesaleRecord_head = CreatManagerFoundWholesaleRecordList(user, date, situation, brand,
                                                                                      taste, package, capacity);
                }
            }
                //修改订单
            else if (select[0] == '2' && strlen(select) == 2) {
                ManagerModifyAnWholesaleOrder(found_wholesaleRecord_head);
            }
                //返回上一界面
            else if (select[0] == '0' && strlen(select) == 2) {
                if (!found_wholesaleRecord_head) { return; }
                else {
                    DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                    found_wholesaleRecord_head = NULL;
                }
            }
                //非法输入
            else {
                printf("非法选择，请重新输入！\n");
                system("read");
            }
        }
    }
}

//管理员进货记录页面
void ManagerViewPurchaseRecordMenu() {
    while (true) {
        char date[MaxSize] = {""};
        char brand[MaxSize] = {""};
        char taste[MaxSize] = {""};
        char package[MaxSize] = {""};
        char capacity[MaxSize] = {""};
        PurchaseRecord *found_purchaseRecord_head = NULL;//创建查询进货记录链表
        while (true) {
            system("cls");
            if (!found_purchaseRecord_head) {
                //管理员查看所有的进货记录
                ViewPurchaseRecords(found_purchaseRecord_head, 0);
                //相关操作
                printf("\n操作\n");
                printf("*********************************\n");
                printf("**********1、查找订单************\n");
                printf("**********2、添加订单************\n");
                printf("**********3、修改订单************\n");
                printf("**********0、退出页面************\n");
                printf("*********************************\n");
                printf("您的选择是：");
            } else {
                //管理员查看搜索到的进货记录
                printf("搜索条件\n");
                printf("**************************************\n");
                printf("订单日期：%s\n", date);
                printf("品牌：%s\n", brand);
                printf("口味：%s\n", taste);
                printf("包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]);
                printf("单瓶容量：%sml\n", capacity);
                printf("**************************************\n");
                ViewPurchaseRecords(found_purchaseRecord_head, 0);
                //相关操作
                printf("\n操作\n");
                printf("*********************************\n");
                printf("**********1、查找订单************\n");
                printf("**********2、添加订单************\n");
                printf("**********3、修改订单************\n");
                printf("**********0、退出搜索页面********\n");
                printf("*********************************\n");
                printf("您的选择是：");
            }
            //输入选择
            char select[MaxSize] = {""};
            fgets(select, sizeof(select), stdin);
            //查找订单
            if (select[0] == '1' && strlen(select) == 2) {
                //销毁查询进货记录链表
                if (found_purchaseRecord_head) {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = NULL;
                }
                //输入查询条件
                if (ManagerInputPurchaseRecordConditions(date, brand, taste, package, capacity) == 1) {
                    //建立查询进货记录链表
                    found_purchaseRecord_head = CreatManagerFoundPurchaseRecordList(date, brand, taste, package,
                                                                                    capacity);
                }
            }
                //添加订单
            else if (select[0] == '2' && strlen(select) == 2) {
                AddAnPurchaseRecordOrder();
                if (found_purchaseRecord_head) {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = CreatManagerFoundPurchaseRecordList(date, brand, taste, package,
                                                                                    capacity);
                }
            }
                //修改订单
            else if (select[0] == '3' && strlen(select) == 2) {
                ManagerModifyPurchaseRecordMenu(found_purchaseRecord_head);
                if (found_purchaseRecord_head) {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = CreatManagerFoundPurchaseRecordList(date, brand, taste, package,
                                                                                    capacity);
                }
            }
                //返回上一界面
            else if (select[0] == '0' && strlen(select) == 2) {
                if (!found_purchaseRecord_head) { return; }
                else {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = NULL;
                }
            }
                //非法输入
            else {
                printf("非法选择，请重新输入！\n");
                system("read");
            }
        }
    }
}

//管理员进货记录修改页面
void ManagerModifyPurchaseRecordMenu(PurchaseRecord *head) {
    //查询订单
    PurchaseRecord *purchase_record = purchaseRecord_head;
    while (true) {
        system("cls");
        ViewPurchaseRecords(head, 0);
        printf("请输入订单号(输入0返回)：");
        char order_number[MaxSize] = {""};
        fgets(order_number, sizeof(order_number), stdin);
        //检测是否返回
        if (order_number[0] == '0' && strlen(order_number) == 2) { return; }
        //查找订单
        while (purchase_record->next) {
            if (isInputCorrect(purchase_record->next->order_number, order_number)) { break; }
            purchase_record = purchase_record->next;
        }
        if (!purchase_record->next) {
            printf("订单不存在！请重新输入！\n");
            system("read");
        } else { break; }
    }
    //修改信息
    while (true) {
        system("cls");
        ViewPurchaseRecords(purchase_record, 1);
        //相关操作
        printf("\n操作\n");
        printf("*******************************\n");
        printf("*********1、修改日期***********\n");
        printf("*********2、修改品牌***********\n");
        printf("*********3、修改口味***********\n");
        printf("*********4、修改包装***********\n");
        printf("*********5、修改单瓶容量*******\n");
        printf("*********6、修改单箱数量*******\n");
        printf("*********7、修改进货价格*******\n");
        printf("*********8、修改进货数量*******\n");
        printf("*********0、退出界面***********\n");
        printf("*******************************\n");
        printf("您的选择是：");
        //输入选择
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //修改日期
        if (select[0] == '1' && strlen(select) == 2) { ModifyPurchaseRecordDate(purchase_record); }
            //修改品牌
        else if (select[0] == '2' && strlen(select) == 2) { ModifyPurchaseRecordBrand(purchase_record); }
            //修改口味
        else if (select[0] == '3' && strlen(select) == 2) { ModifyPurchaseRecordTaste(purchase_record); }
            //修改包装
        else if (select[0] == '4' && strlen(select) == 2) { ModifyPurchaseRecordPackage(purchase_record); }
            //修改单瓶容量
        else if (select[0] == '5' && strlen(select) == 2) { ModifyPurchaseRecordBottleCapacity(purchase_record); }
            //修改单箱数量
        else if (select[0] == '6' && strlen(select) == 2) { ModifyPurchaseRecordBoxQuantity(purchase_record); }
            //修改进货价格
        else if (select[0] == '7' && strlen(select) == 2) { ModifyPurchaseRecordRestockingPrice(purchase_record); }
            //修改进货数量
        else if (select[0] == '8' && strlen(select) == 2) { ModifyPurchaseRecordGoodsQuantity(purchase_record); }
            //返回上一界面
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}