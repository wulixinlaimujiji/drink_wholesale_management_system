#include "manager.h"
#include "user.h"
extern Manager* manager;
extern User* user_head;
extern Drink* drink_head;
extern WholesaleRecord* wholesaleRecord_head;
extern PurchaseRecord* purchaseRecord_head;

/*登录部分*/
//登录管理员账号
bool ManagerLogin() {
    //输入账号,检测账号是否存在
    char ID[MaxSize] = { "" };
    while (true) {
        system("clear");
        //输入账号
        printf("请输入账号(输入0返回管理员登录界面)：");
        fgets(ID, sizeof(ID), stdin);
        //检测是否返回管理员登录界面
        if (ID[0] == '0' && strlen(ID) == 2) { return false; }
        //检测账号是否存在
        if (isInputCorrect(manager->ID, ID)) { break; }
        else {
            printf("账号错误，请重新输入！\n");
            system("read");
        }
    }
    //输入密码，检测密码是否正确
    while (true) {
        system("clear");
        printf("请输入账号：%s\n", ID);
        //输入密码
        printf("请输入密码（输入0返回管理员登录界面）：");
        char password[MaxSize] = { "" };
        fgets(password, sizeof(password), stdin);
        //检测是否返回管理员登录界面
        if (password[0] == '0' && strlen(password) == 2) { return false; }
        //检测密码是否正确
        if (isInputCorrect(manager->password, password)) {
            printf("登录成功！\n");
            system("read");
            return true;
        }
        else {
            printf("密码错误，请重新输入！\n");
            system("read");
        }
    }
}
//忘记管理员密码
void ForgotManagerPassword() {
    //输入账号,检测账号是否存在
    while (true) {
        system("clear");
        //输入账号
        printf("请输入账号(输入0返回管理员登录界面)：");
        char ID[MaxSize] = { "" };
        fgets(ID, sizeof(ID), stdin);
        //检测是否返回管理员登录界面
        if (ID[0] == '0' && strlen(ID) == 2) { return; }
        //检测账号是否存在
        if (isInputCorrect(manager->ID, ID)) { break; }
        else {
            printf("账号错误，请重新输入！\n");
            system("read");
        }
    }
    //输入电话号码，验证身份
    char Tel[MaxSize] = { "" };
    while (true) {
        system("clear");
        printf("请输入账号：%s\n", manager->ID);
        //输入电话号码
        printf("请输入电话号码(输入0返回管理员登录界面)：");
        fgets(Tel, sizeof(Tel), stdin);
        //检测是否返回管理员登录界面
        if (Tel[0] == '0' && strlen(Tel) == 2) { return; }
        //检测电话号码是否正确
        if (isInputCorrect(manager->Tel, Tel)) { break; }
        else {
            printf("电话号码错误，请重新输入！\n");
            system("read");
        }
    }
    //重置密码
    while (true) {
        system("clear");
        printf("请输入账号：%s\n", manager->ID);
        printf("请输入电话号码：%s\n", Tel);
        //输入新密码
        printf("请输入新密码(需含同时含有大小写字母与数字，且密码为10~20位)(输入0返回管理员登录界面)：");
        char new_password1[MaxSize] = { "" };
        fgets(new_password1, sizeof(new_password1), stdin);
        //检测是否返回管理员登录界面
        if (new_password1[0] == '0' && strlen(new_password1) == 2) { return; }
        //检测新密码是否规范
        if (!isPasswordAllowed(new_password1)) {
            printf("密码不符合规范，请重新输入！\n");
            system("read");
            continue;
        }
        //确认新密码
        while (true) {
            system("clear");
            printf("请输入账号：%s\n", manager->ID);
            printf("请输入电话号码：%s\n", Tel);
            printf("请输入新密码：%s\n", new_password1);
            //确认密码
            printf("请确认新密码(输入0重新输入新密码)：");
            char new_password2[MaxSize] = { "" };
            fgets(new_password2, sizeof(new_password2), stdin);
            //检测是否重新输入新密码
            if (new_password2[0] == '0' && strlen(new_password2) == 2) { break; }
            //检测两次输入的密码是否一致
            if (isInputCorrect(new_password1, new_password2)) {
                for (int i = 0; new_password1[i] != '\0'; i++) {
                    manager->password[i] = new_password1[i];
                }
                manager->password[strlen(new_password1)] = '\0';
                //密码重置成功
                RenewManagerFile();
                printf("密码重置成功！\n");
                system("read");
                return;
            }
            else {
                printf("两次密码不一致，请重新输入！\n");
                system("read");
            }
        }
    }
}

/*管理员信息部分*/
//查看管理员信息
void ManagerInformation() {
    printf("账户信息\n");
    printf("*****************************\n");
    printf("*****账号: %s\n", manager->ID);
    printf("*****联系方式：%s\n", manager->Tel);
    printf("*****资金: %.2f\n", manager->fund);
    printf("*****************************\n");
}
//修改联系方式
void ModifyManagerTel() {
    while (true) {
        //输入新联系方式
        system("clear");
        printf("请输入新的11位手机号码(输入0返回)：");
        char new_Tel[MaxSize] = { "" };
        fgets(new_Tel, sizeof(new_Tel), stdin);
        //检测是否返回上一页面
        if (new_Tel[0] == '0' && strlen(new_Tel) == 2) { return; }
        //联系方式符合规范，则保存联系方式
        if (isNumberAllowed(new_Tel) && strlen(new_Tel) == 11) {
            for (int i = 0; new_Tel[i] != '\0'; i++) {
                manager->Tel[i] = new_Tel[i];
            }
            manager->Tel[11] = '\0';
            //修改成功
            RenewManagerFile();
            printf("修改成功！\n");
            system("read");
            return;
        }
            //联系方式不符合规范，则重新输入
        else {
            printf("手机号码格式错误，请重新输入！\n");
            system("read");
        }
    }
}
//修改管理员密码
void ModifyManagerPassword() {
    //输入密码，检测密码是否正确
    while (true) {
        system("clear");
        printf("账号：%s\n", manager->ID);
        //输入密码
        printf("请输入密码（输入0返回）：");
        char password[MaxSize] = { "" };
        fgets(password, sizeof(password), stdin);
        //检测是否返回
        if (password[0] == '0' && strlen(password) == 2) { return; }
        //检测密码是否正确
        if (isInputCorrect(manager->password, password)) { break; }
        else {
            printf("密码错误，请重新输入！\n");
            system("read");
        }
    }
    //重置密码
    while (true) {
        system("clear");
        printf("账号：%s\n", manager->ID);
        printf("请输入密码：%s\n", manager->password);
        //输入新密码
        printf("请输入新密码(需含同时含有大小写字母与数字，，且密码为10~20位)(输入0返回)：");
        char new_password1[MaxSize] = { "" };
        fgets(new_password1, sizeof(new_password1), stdin);
        //检测是否返回
        if (new_password1[0] == '0' && strlen(new_password1) == 2) { return; }
            //检测新密码是否规范
        else if (!isPasswordAllowed(new_password1)) {
            printf("密码不符合规范，请重新输入！\n");
            system("read");
            continue;
        }
        //确认新密码
        while (true) {
            system("clear");
            printf("账号：%s\n", manager->ID);
            printf("请输入密码：%s\n", manager->password);
            printf("请输入新密码：%s\n", new_password1);
            //确认密码
            printf("请确认新密码(输入0重新输入新密码)：");
            char new_password2[MaxSize] = { "" };
            fgets(new_password2, sizeof(new_password2), stdin);
            //检测是否重新输入新密码
            if (new_password2[0] == '0' && strlen(new_password2) == 2) { break; }
            //检测两次输入的密码是否一致
            if (isInputCorrect(new_password1, new_password2)) {
                for (int i = 0; new_password1[i] != '\0'; i++) {
                    manager->password[i] = new_password1[i];
                }
                manager->password[strlen(new_password1)] = '\0';
                //密码重置成功
                RenewManagerFile();
                printf("密码重置成功！\n");
                system("read");
                return;
            }
            else {
                printf("两次密码不一致，请重新输入！\n");
                system("read");
            }
        }
    }
}

/*用户信息部分*/
//查看用户信息
void UserInformation(User* head, int identity) {
    if (!identity) { printf("用户信息\n"); }
    else { printf("个人信息\n"); }
    printf("*****************************\n");
    int num = 1;
    User* user = NULL;
    if (!head) { user = user_head->next; }
    else { user = head; }
    while (user) {
        if (!head) { printf("*%d*账号：%s\n", num++, user->ID); }
        else { printf("    账号：%s\n", user->ID); }
        printf("    网点名称：%s\n", user->name);
        printf("    会员等级：%d\n", user->level);
        printf("    收货地址：%s\n", user->address);
        printf("    联系方式：%s\n", user->Tel);
        printf("    账户余额：%.2f\n", user->total_funding);
        printf("    账户消费：%.2f\n\n", user->total_consumption);
        user = user->next;
        if (head) { break; }
    }
    printf("*****************************\n");
}
//重置用户密码
void ResetUserPassword(User* user) {
    while (true) {
        system("clear");
        UserInformation(user, 1);
        printf("是否确认重置用户密码(1是，2否)\n");
        printf("请输入您的选择：");
        char select[MaxSize] = { "" };
        fgets(select, sizeof(select), stdin);
        //确认重置
        if (select[0] == '1' && strlen(select) == 2) {
            strcpy(user->password, "Xx123456789");
            RenewUserFile();
            printf("密码重置为：Xx123456789！\n");
            system("read");
            return;
        }
            //取消重置
        else if (select[0] == '2' && strlen(select) == 2) { return; }
            //非法输入
        else {
            printf("非法选择，请重新输入！\n");
            system("read");
        }
    }
}


/*酒水部分*/
//查看在售酒水
void ViewAvailableDrinks(Drink* head, int identity, int type) {
    //确定链表
    Drink* drink = NULL;
    if (head) { drink = head->next; }
    else { drink = drink_head->next; }
    //输出酒水信息
    if (!type) {
        printf("在售酒水\n");
        printf("************************************\n");
    }
    while (drink) {
        if (!type) {
            printf("*编号：%s\n", drink->ID);
            printf(" 品牌：%s\n", drink->brand);
        }
        else { printf(" 品牌：%s\n", drink->brand); }
        printf(" 口味：%s\n", drink->taste);
        if (drink->package == 1) {
            printf(" 包装种类：瓶装\n");
            printf(" 单瓶容量：%smL/瓶\n", drink->single_bottle_capacity);
            printf(" 单箱数量：%s瓶/箱\n", drink->single_box_quantity);
        }
        else if (drink->package == 2) {
            printf(" 包装种类：罐装\n");
            printf(" 单罐容量：%smL/罐\n", drink->single_bottle_capacity);
            printf(" 单箱数量：%s罐/箱\n", drink->single_box_quantity);
        }
        else {
            printf(" 包装种类：盒装\n");
            printf(" 单盒容量：%smL/盒\n", drink->single_bottle_capacity);
            printf(" 单箱数量：%s盒/箱\n", drink->single_box_quantity);
        }
        if (!identity) { printf(" 进货价格：%.2f元/箱\n", drink->restocking_price); }
        printf(" 销售价格：%.2f元/箱\n", drink->sale_price);
        printf(" 库存数量：%d箱\n", drink->stock_quantity);
        if (drink->activity.form == 0) {
            printf(" 优惠活动：无\n\n");
        }
        else {
            if (drink->activity.form == 1) {
                printf(" 优惠活动：%.1f折\n", drink->activity.specific_1 * 10);
            }
            else {
                printf(" 优惠活动：买%d箱送%d箱\n", drink->activity.specific_2[0], drink->activity.specific_2[1]);
            }
            printf(" 优惠原因：%s\n", drink->activity.reason);
            printf(" 活动时间：%s ~ %s\n\n", drink->activity.date[0], drink->activity.date[1]);
        }
        drink = drink->next;
        if (type == 1) { return; }
    }
    printf("************************************\n");
}
//输入酒水查询条件
int InputDrinkConditions(char* brand, char* taste, char* package, char* capacity, char* activity) {
    int flag = 0;
    while (true) {
        system("clear");
        if (flag > 0) { printf("请输入品牌：%s\n", brand); }
        if (flag > 1) { printf("请输入口味：%s\n", taste); }
        if (flag > 2) { printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]); }
        if (flag > 3) { printf("请输入单瓶容量：%smL\n", capacity); }
        if (flag > 4) { printf("请输入优惠活动(1折扣，2赠品，3不限)：%c\n", activity[0]); }
        //酒水品牌
        while (!flag) {
            system("clear");
            printf("请输入品牌(无需直接回车)(输入0返回)：");
            fgets(brand, sizeof(brand), stdin);
            if (brand[0] == '0' && strlen(brand) == 2) { return 0; }
            else { flag = 1; break; }
        }
        //酒水口味
        while (flag == 1) {
            printf("请输入口味(无需直接回车)(输入0重选品牌)：");
            fgets(taste, sizeof(taste), stdin);
            if (taste[0] == '0' && strlen(taste) == 2) { flag = 0; }
            else { flag = 2; break; }
        }
        //包装种类
        while (flag == 2) {
            printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)(输入0重选口味)：");
            int result = isPackageCorrect(package, 1);
            if (!result) { flag = 1; }
            else if (result == 1) { flag = 3; }
            else { break; }
        }
        //单瓶容量
        while (flag == 3) {
            printf("请输入单瓶容量(mL)(无需直接回车)(输入0重选包装种类)：");
            fgets(capacity, sizeof(capacity), stdin);
            if (capacity[0] == '0' && strlen(capacity) == 2) { flag = 2; }
            else { flag = 4; }
        }
        //优惠活动
        while (flag == 4) {
            printf("请输入优惠活动(1折扣，2赠品，3不限)(输入0重选容量)：");
            fgets(activity, sizeof(activity), stdin);
            if (activity[0] == '0' && strlen(activity) == 2) { flag = 3; break; }
            else if (activity[0] == '1' && strlen(activity) == 2) { flag = 5; break; }
            else if (activity[0] == '2' && strlen(activity) == 2) { flag = 5; break; }
            else if (activity[0] == '3' && strlen(activity) == 2) { flag = 5; break; }
            else if (activity[0] == '4' && strlen(activity) == 2) { flag = 5; break; }
            else {
                printf("非法选择，请重新输入！\n");
                system("read");
            }
        }
        //确定设置完成
        while (flag == 5) {
            printf("是否确定搜索(1是，2否)：");
            int result = isSure();
            if (!result) { return 1; }
            else if (result == 1) { flag = 4; }
            else { break; }
        }
    }
}
//创建按条件搜索酒水链表
Drink* CreatFoundDrinkList(char* brand, char* taste, char* package, char* capacity, char* activity) {
    //创建哨兵结点
    Drink* head = (Drink*)malloc(sizeof(Drink));
    Drink* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    //寻找酒水
    Drink* drink = drink_head->next;
    while (drink) {
        //检验包装种类
        if (package[0] != '4' && drink->package != (package[0] - '0')) { drink = drink->next; continue; }
        //检验容量
        if (strlen(capacity) != 0 && !isInputCorrect(drink->single_bottle_capacity, capacity)) { drink = drink->next; continue; }
        //检验品牌
        if (strlen(brand) != 0 && !isInclude(drink->brand, brand)) { drink = drink->next; continue; }
        //检验口味
        if (strlen(taste) != 0 && !isInclude(drink->taste, taste)) { drink = drink->next; continue; }
        //检验活动
        if (activity[0] != '3' && drink->activity.form != (activity[0] - '0')) { drink = drink->next; continue; }
        //通过检验则将其加入按条件搜索酒水链表
        //创建结点
        Drink* temp = (Drink*)malloc(sizeof(Drink));
        if (!temp) {
            printf("内存分配失败");
            return NULL;
        }
        strcpy(temp->ID, drink->ID);//酒水编号
        strcpy(temp->brand, drink->brand);//酒水品牌
        strcpy(temp->taste, drink->taste);//酒水口味
        temp->package = drink->package;//包装种类
        strcpy(temp->single_bottle_capacity, drink->single_bottle_capacity);//单瓶容量
        strcpy(temp->single_box_quantity, drink->single_box_quantity);//单箱数量
        temp->restocking_price = drink->restocking_price;//进货价格
        temp->sale_price = drink->sale_price;//销售价格
        temp->stock_quantity = drink->stock_quantity;//库存数量
        temp->activity.form = drink->activity.form; //优惠形式
        temp->activity.specific_1 = drink->activity.specific_1;//具体折扣
        for (int i = 0; i < 2; i++) {//具体赠品
            temp->activity.specific_2[i] = drink->activity.specific_2[i];
        }
        strcpy(temp->activity.reason, drink->activity.reason);//优惠原因
        for (int i = 0; i < 2; i++) { //活动时间
            strcpy(temp->activity.date[i], drink->activity.date[i]);
        }
        temp->next = NULL;
        //加入链表
        tail->next = temp;
        tail = temp;
        drink = drink->next;
    }
    return head;
}
//销毁查询酒水链表
void DestroyFoundDrinkList(Drink* head) {
    while (head) {
        Drink* temp = head;
        head = head->next;
        free(temp);
    }
}
//修改销售价格
void ModifyDrinkSalePrice(Drink* drink) {
    while (true) {
        system("clear");
        ViewAvailableDrinks(drink, 0, 1);
        printf("请输入新销售价格(输入0返回)：");
        char price[MaxSize] = { "" };
        int result = isPriceCorrect(price);
        if (!result) { return; }
        else if (result == 1) {
            drink->next->sale_price = atoi(price);
            RenewDrinkFile();
            printf("销售价格修改成功！\n");
            system("read");
            return;
        }
    }
}
//设置优惠活动
void SetActivity(Drink* head, int type) {
    //设置活动信息
    char discount_form[MaxSize] = { "" };
    char specific_discount_1[MaxSize] = { "" };
    char specific_discount_2[MaxSize] = { "" };
    char discount_reason[MaxSize] = { "无" };
    char discount_date_start[MaxSize] = { "2000-01-01_00:00:00" };
    char discount_date_end[MaxSize] = { "2000-01-01_00:00:00" };
    int flag = 0;
    while (flag != 7) {
        system("clear");
        if (flag > 0) {
            if (discount_form[0] == '1') { printf("优惠形式：折扣\n"); }
            if (discount_form[0] == '2') { printf("优惠形式：赠品\n"); }
        }
        if (flag > 2) {
            if (discount_form[0] == '1') { printf("具体折扣：%s\n", specific_discount_1); }
            if (discount_form[0] == '2') { printf("买%s箱送%s箱\n", specific_discount_1, specific_discount_2); }
        }
        if (flag > 3) { printf("活动原因：%s\n", discount_reason); }
        if (flag > 4) { printf("活动开始时间：%s\n", discount_date_start); }
        if (flag > 5) { printf("活动结束时间：%s\n", discount_date_end); }
        //设置优惠形式
        while (!flag) {
            printf("请选择活动的优惠形式(0返回，1折扣，2赠品，3取消活动)：");
            fgets(discount_form, sizeof(discount_form), stdin);
            if (discount_form[0] == '1' && strlen(discount_form) == 2) { flag = 1; break; }
            else if (discount_form[0] == '2' && strlen(discount_form) == 2) { flag = 2; break; }
            else if (discount_form[0] == '3' && strlen(discount_form) == 2) { flag = 7; break; }
            else if (discount_form[0] == '0' && strlen(discount_form) == 2) { return; }
            else {
                printf("非法选择，请重新输入！\n");
                system("read");
            }
        }
        //折扣优惠
        while (flag == 1) {
            printf("请输入具体折扣(0.00~0.99)(输入0重选优惠形式)：");
            int result = isDiscountCorrect(specific_discount_1);
            if (!result) { flag = 0; }
            else if (result == 1) { flag = 3; }
            else { break; }
        }
        //赠品优惠
        while (flag == 2) {
            printf("请输入购买箱数与赠送箱数(输入0返回)：");
            scanf("%s", specific_discount_1);
            scanf("%s", specific_discount_2);
            if (specific_discount_1[0] == '0' && strlen(specific_discount_1) == 2) { flag = 0; break; }
            if (strlen(specific_discount_1) && isNumberAllowed(specific_discount_1) && strlen(specific_discount_2) && isNumberAllowed(specific_discount_2)) { flag = 3; break; }
            else {
                printf("箱数错误，请重新输入！\n");
                system("read");
            }
        }
        //活动原因
        while (flag == 3) {
            printf("请输入活动原因(输入0重置具体优惠)：");
            int result = isReasonCorrect(discount_reason);
            if (!result) {
                if (discount_form[0] == '1') { flag = 1; }
                else { flag = 2; }
            }
            else  if (result == 1) { flag = 4; }
            else { break; }
        }
        //活动开始时间
        while (flag == 4) {
            printf("请输入活动开始时间(xxxx-xx-xx_xx:xx:xx)(输入0重置活动原因)：");
            fgets(discount_date_start, sizeof(discount_date_start), stdin);
            if (discount_date_start[0] == '0' && strlen(discount_date_start) == 2) { flag = 3; break; }
            if (isTimeAllowed(discount_date_start)) { flag = 5; break; }
            else {
                printf("活动开始时间错误，请重新输入！\n");
                system("read");
                break;
            }
        }
        //活动结束时间
        while (flag == 5) {
            printf("请输入活动结束时间(xxxx-xx-xx_xx:xx:xx)(输入0重置活动开始时间)：");
            fgets(discount_date_end, sizeof(discount_date_end), stdin);
            if (discount_date_end[0] == '0' && strlen(discount_date_end) == 2) { flag = 4; break; }
            if (isTimeAllowed(discount_date_start)) {
                char date[20];
                time_t current_time;
                struct tm* time_info;
                time(&current_time);
                time_info = localtime(&current_time);
                strftime(date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
                if (isChronological(date, discount_date_end) && isChronological(discount_date_start, discount_date_end)) { flag = 6; break; }
            }
            printf("活动结束时间错误，请重新输入！\n");
            system("read");
            break;
        }
        //确定设置完成
        while (flag == 6) {
            printf("确认设置活动吗(1是，2否)");
            int result = isSure();
            if (!result) { flag = 7; }
            else if (result == 1) { flag = 5; }
            else { break; }
        }
    }
    //保存信息
    Drink* drink = NULL;
    if (type == 1) {
        drink = head->next;
        drink->activity.form = discount_form[0] - '0';
        if (drink->activity.form == 1) {
            drink->activity.specific_1 = (specific_discount_1[0] - '0') + 0.1 * (float)(specific_discount_1[2] - '0') + 0.01 * (float)(specific_discount_1[3] - '0');
            drink->activity.specific_2[0] = 0;
            drink->activity.specific_2[1] = 0;
        }
        else if (drink->activity.form == 2) {
            drink->activity.specific_1 = 1;
            drink->activity.specific_2[0] = atoi(specific_discount_1);
            drink->activity.specific_2[1] = atoi(specific_discount_2);
        }
        else {
            drink->activity.form = 0;
            drink->activity.specific_1 = 1;
            drink->activity.specific_2[0] = 0;
            drink->activity.specific_2[1] = 0;
        }
        strcpy(drink->activity.reason, discount_reason);
        strcpy(drink->activity.date[0], discount_date_start);
        strcpy(drink->activity.date[1], discount_date_end);
    }
    else {
        drink = drink_head->next;
        if (!head) {
            while (drink) {
                drink->activity.form = discount_form[0] - '0';
                if (drink->activity.form == 1) {
                    drink->activity.specific_1 = (specific_discount_1[0] - '0') + 0.1 * (float)(specific_discount_1[2] - '0') + 0.01 * (float)(specific_discount_1[3] - '0');
                    drink->activity.specific_2[0] = 0;
                    drink->activity.specific_2[1] = 0;
                }
                else if (drink->activity.form == 2) {
                    drink->activity.specific_1 = 1;
                    drink->activity.specific_2[0] = atoi(specific_discount_1);
                    drink->activity.specific_2[1] = atoi(specific_discount_2);
                }
                else {
                    drink->activity.form = 0;
                    drink->activity.specific_1 = 1;
                    drink->activity.specific_2[0] = 0;
                    drink->activity.specific_2[1] = 0;
                }
                strcpy(drink->activity.reason, discount_reason);
                strcpy(drink->activity.date[0], discount_date_start);
                strcpy(drink->activity.date[1], discount_date_end);
                drink = drink->next;
            }
        }
        else {
            Drink* found_drink = head->next;
            while (drink && found_drink) {
                if (isInputCorrect(drink->ID, found_drink->ID)) {
                    drink->activity.form = discount_form[0] - '0';
                    if (drink->activity.form == 1) {
                        drink->activity.specific_1 = (specific_discount_1[0] - '0') + 0.1 * (float)(specific_discount_1[2] - '0') + 0.01 * (float)(specific_discount_1[3] - '0');
                        drink->activity.specific_2[0] = 0;
                        drink->activity.specific_2[1] = 0;
                    }
                    else if (drink->activity.form == 2) {
                        drink->activity.specific_1 = 1;
                        drink->activity.specific_2[0] = atoi(specific_discount_1);
                        drink->activity.specific_2[1] = atoi(specific_discount_2);
                    }
                    else {
                        drink->activity.form = 0;
                        drink->activity.specific_1 = 1;
                        drink->activity.specific_2[0] = 0;
                        drink->activity.specific_2[1] = 0;
                    }
                    strcpy(drink->activity.reason, discount_reason);
                    strcpy(drink->activity.date[0], discount_date_start);
                    strcpy(drink->activity.date[1], discount_date_end);
                    drink = drink->next;
                    found_drink = found_drink->next;
                }
                else {
                    drink = drink->next;
                }
            }
        }
    }
    RenewDrinkFile();
    printf("活动设置成功！\n");
    system("read");
}
//下架酒水
void TakeDownDrink(Drink* head, int type) {
    //确认下架
    while (true) {
        printf("确认下架这些酒水吗(1是，2否)");
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; };
    }
    //下架
    Drink* drink = NULL;
    if (type == 1) {
        drink = head->next;
        head->next = drink->next;
        free(drink);
    }
    else {
        if (!head) {
            while (drink_head->next) {
                drink = drink_head->next;
                drink_head->next = drink->next;
                free(drink);
            }
        }
        else {
            Drink* found_drink = head->next;
            drink = drink_head;
            while (drink && found_drink) {
                if (isInputCorrect(drink->next->ID, found_drink->ID)) {
                    Drink* temp = drink->next;
                    drink->next = temp->next;
                    free(temp);
                    found_drink = found_drink->next;
                }
                else { drink = drink->next; }
            }
        }
    }
    RenewDrinkFile();
    printf("下架成功！\n");
    system("read");
}


/*信息部分*/
//接受下单
void AcceptOrder() {
    //查找订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("clear");
        ViewWholesaleRecords(wholesale_record, NULL, 1, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        else if (!wholesale_record->next || wholesale_record->next->goods_situation != 1) {
            wholesale_record = NULL;
            printf("未找到订单，请重新输入！\n");
            system("read");
        }
        else { break; }
    }
    //接受下单
    while (true) {
        system("clear");
        ViewWholesaleRecords(wholesale_record, NULL, 1, 1);
        printf("确定接受订单吗(1是，2否)\n");
        printf("请输入您的选择：");
        char select[MaxSize] = { "" };
        fgets(select, sizeof(select), stdin);
        if (select[0] == '1' && strlen(select) == 2) { break; }
        else if (select[0] == '2' && strlen(select) == 2) { return; }
        else {
            printf("非法选择，请重新输入");
            system("read");
        }
    }
    //更新信息
    wholesale_record->next->goods_situation = 2;
    RenewDrinkFile();
    printf("接受成功！\n");
    system("read");
}
//接受退单
void AcceptReturn() {
    //查找订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("clear");
        ViewWholesaleRecords(wholesale_record, NULL, 4, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        if (!wholesale_record->next || wholesale_record->next->goods_situation != 4) {
            wholesale_record = NULL;
            printf("未找到订单，请重新输入！\n");
            system("read");
        }
        else { break; }
    }
    //接受退单
    while (true) {
        system("clear");
        ViewWholesaleRecords(wholesale_record, NULL, 4, 1);
        printf("确定接受退货吗(1是，2否)\n");
        printf("请输入您的选择：");
        char select[MaxSize] = { "" };
        fgets(select, sizeof(select), stdin);
        if (select[0] == '1' && strlen(select) == 2) { break; }
        else if (select[0] == '2' && strlen(select) == 2) { return; }
        else {
            printf("非法选择，请重新输入");
            system("read");
        }
    }
    //更新信息
    //更新批发记录
    wholesale_record->next->goods_situation = 5;
    RenewWholesaleRecordFile();
    //更新用户信息
    User* user = isUserExist(wholesale_record->next->user_ID);
    float price = wholesale_record->next->goods_quantity * wholesale_record->next->past_drink.sale_price;
    for (int i = 0; i < 3; i++) {
        price *= wholesale_record->next->discount[i].specific_1;
    }
    user->total_funding += price;
    user->total_consumption -= price;
    RenewUserFile();
    //更新酒水信息
    Drink* drink = isDrinkExist(wholesale_record->next->past_drink.ID);
    int gift_box = wholesale_record->next->discount[2].specific_2[0];
    if (wholesale_record->next->discount[1].form == 2) {
        gift_box += wholesale_record->next->goods_quantity / wholesale_record->next->discount[1].specific_2[0] * wholesale_record->next->discount[1].specific_2[1];
    }
    drink->stock_quantity += wholesale_record->next->goods_quantity + gift_box;
    RenewDrinkFile();
}

/*批发部分*/
//查看批发记录
void ViewWholesaleRecords(WholesaleRecord* head, User* user, int situation, int type) {
    WholesaleRecord* wholesale_record;
    if (head) { wholesale_record = head->next; }
    else { wholesale_record = wholesaleRecord_head->next; }
    printf("订单记录\n");
    printf("************************************\n");
    while (wholesale_record) {
        if (situation == 6 || wholesale_record->goods_situation == situation) {
            if (user && !isInputCorrect(wholesale_record->user_ID, user->ID)) { wholesale_record = wholesale_record->next; continue; }
            //输出信息
            printf("*订单号：%s\n", wholesale_record->order_number);
            printf(" 订单日期：%s\n", wholesale_record->date);
            if (!user) { printf(" 用户账号：%s\n", wholesale_record->user_ID); }
            printf(" 酒水编号：%s\n", wholesale_record->past_drink.ID);
            printf(" 酒水品牌：%s\n", wholesale_record->past_drink.brand);
            printf(" 酒水口味：%s\n", wholesale_record->past_drink.taste);
            if (wholesale_record->past_drink.package == 1) {
                printf(" 单瓶容量：%smL/瓶\n", wholesale_record->past_drink.single_bottle_capacity);
                printf(" 单箱数量：%s瓶/箱\n", wholesale_record->past_drink.single_box_quantity);
            }
            else if (wholesale_record->past_drink.package == 2) {
                printf(" 单罐容量：%smL/罐\n", wholesale_record->past_drink.single_bottle_capacity);
                printf(" 单箱数量：%s罐/箱\n", wholesale_record->past_drink.single_box_quantity);
            }
            else {
                printf(" 单盒容量：%smL/盒\n", wholesale_record->past_drink.single_bottle_capacity);
                printf(" 单箱数量：%s盒/箱\n", wholesale_record->past_drink.single_box_quantity);
            }
            printf(" 销售价格：%.2f元/箱\n", wholesale_record->past_drink.sale_price);
            printf(" 批发数量：%d箱\n", wholesale_record->goods_quantity);
            float price = wholesale_record->goods_quantity * wholesale_record->past_drink.sale_price;
            for (int i = 0; i < 2; i++) {
                if (wholesale_record->discount[i].form == 1) {
                    printf(" 优惠活动：%.1f折\n", wholesale_record->discount[i].specific_1 * 10);
                    printf(" 优惠原因：%s\n", wholesale_record->discount[i].reason);
                    price *= wholesale_record->discount[i].specific_1;
                }
                else if (wholesale_record->discount[i].form == 2) {
                    printf(" 优惠活动：买%d箱送%d箱\n", wholesale_record->discount->specific_2[0], wholesale_record->discount->specific_2[1]);
                    printf(" 优惠原因：%s\n", wholesale_record->discount[i].reason);
                }
            }
            if (wholesale_record->discount[2].form == 1) {
                printf(" 赔偿：%.1f折\n", wholesale_record->discount[2].specific_1 * 10);
                printf(" 赔偿原因：%s\n", wholesale_record->discount[2].reason);
                price *= wholesale_record->discount[2].specific_1;
            }
            else if (wholesale_record->discount[2].form == 2) {
                printf(" 赔偿：%d箱\n", wholesale_record->discount[2].specific_2[0]);
                printf(" 赔偿原因：%s\n", wholesale_record->discount[2].reason);
            }
            printf(" 订单价格：%.2f\n", price);
            if (wholesale_record->goods_situation == 1) { printf(" 订单现状：已下单\n\n"); }
            else if (wholesale_record->goods_situation == 2) { printf(" 订单现状：已发货\n\n"); }
            else if (wholesale_record->goods_situation == 3) { printf(" 订单现状：已收货\n\n"); }
            else if (wholesale_record->goods_situation == 4) { printf(" 订单现状：申请退货\n\n"); }
            else { printf(" 订单现状：已退货\n\n"); }
        }
        wholesale_record = wholesale_record->next;
        if (type == 1) { break; }
    }
    printf("************************************\n");
}
//输入查询条件
int ManagerInputWholesaleRecordConditions(char* user, char* date, char* situation, char* brand, char* taste, char* package, char* capacity) {
    int flag = 0;
    while (true) {
        system("clear");
        if (flag > 0) { printf("请输入用户账号或联系方式：%s\n", user); }
        if (flag > 1) { printf("请输入订单日期：%s\n", date); }
        if (flag > 2) { printf("请输入订单现状(1已下单，2派送中，3已到货，4申请退货，5已退货，6不限)：%c\n", situation[0]); }
        if (flag > 3) { printf("请输入品牌：%s\n", brand); }
        if (flag > 4) { printf("请输入口味：%s\n", taste); }
        if (flag > 5) { printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]); }
        if (flag > 6) { printf("请输入单瓶容量：%smL\n", capacity); }
        //用户账号或联系方式
        while (!flag) {
            //输入账号或联系方式
            printf("请输入用户账号或联系方式(无需直接回车)(输入0返回)：");
            char input[MaxSize] = { "" };
            fgets(input, sizeof(input), stdin);
            if (input[0] == '0' && strlen(input) == 2) { return 0; }
            User* p = isUserExist(input);
            if (p) {
                strcpy(user, p->ID);
                flag = 1;
                break;
            }
            if (!strlen(input)) { flag = 1; break; }
            else {
                printf("用户不存在，请重新输入！\n");
                system("read");
                break;
            }
        }
        //订单日期
        while (flag == 1) {
            printf("请输入订单日期(xxxx-xx-xx)(无需直接回车)(输入0重选用户)：");
            fgets(date, sizeof(date), stdin);
            if (date[0] == '0' && strlen(date) == 2) { flag = 0; }
            else { flag = 2; }
        }
        //订单现状
        while (flag == 2) {
            printf("请输入订单现状(1已下单，2派送中，3已到货，4申请退货，5已退货，6不限)(输入0重选订单日期)：");
            int result = isSituationCorrect(situation);
            if (!result) { flag = 1; }
            else if (result == 1) { flag = 3; }
            else { break; }
        }
        //酒水品牌
        while (flag == 3) {
            printf("请输入品牌(无需直接回车)(输入0重选订单现状)：");
            fgets(brand, sizeof(brand), stdin);
            if (brand[0] == '0' && strlen(brand) == 2) { flag = 2; break; }
            else { flag = 4; break; }
        }
        //酒水口味
        while (flag == 4) {
            printf("请输入口味(无需直接回车)(输入0重选品牌)：");
            fgets(taste, sizeof(taste), stdin);
            if (taste[0] == '0' && strlen(taste) == 2) { flag = 3; }
            else { flag = 5; }
        }
        //包装种类
        while (flag == 5) {
            printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)(输入0重选口味)：");
            int result = isPackageCorrect(package, 1);
            if (!result) { flag = 4; }
            else if (result == 1) { flag = 6; }
            else { break; }
        }
        //单瓶容量
        while (flag == 6) {
            printf("请输入单瓶容量mL(无需直接回车)(输入0重选包装)：");
            fgets(capacity, sizeof(capacity), stdin);
            if (capacity[0] == '0' && strlen(capacity) == 2) { flag = 5; }
            else { flag = 7; }
        }
        //确定设置完成
        while (flag == 7) {
            printf("是否确定搜索(1是，2否)：");
            int result = isSure();
            if (!result) { return 1; }
            else if (result == 1) { flag = 6; }
            else { break; }
        }
    }
}
//建立查询批发记录链表
WholesaleRecord* CreatManagerFoundWholesaleRecordList(char* user, char* date, char* situation, char* brand, char* taste, char* package, char* capacity) {
    //创建哨兵结点
    WholesaleRecord* head = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
    WholesaleRecord* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    //寻找批发记录
    WholesaleRecord* wholesale_record = wholesaleRecord_head->next;
    while (wholesale_record) {
        ///查找满足条件的记录
        //检验用户
        if (strlen(user) != 0 && !isInputCorrect(wholesale_record->user_ID, user)) { wholesale_record = wholesale_record->next; continue; }
        //检验订单日期
        if (strlen(date) != 0 && !isInclude(wholesale_record->date, date)) { wholesale_record = wholesale_record->next; continue; }
        //检验订单状态
        if (situation[0] != '6' && wholesale_record->goods_situation != (situation[0] - '0')) { wholesale_record = wholesale_record->next; continue; }
        //检验包装种类
        if (package[0] != '4' && wholesale_record->past_drink.package != (package[0] - '0')) { wholesale_record = wholesale_record->next; continue; }
        //检验容量
        if (strlen(capacity) != 0 && !isInputCorrect(wholesale_record->past_drink.single_bottle_capacity, capacity)) { wholesale_record = wholesale_record->next; continue; }
        //检验品牌
        if (strlen(brand) != 0 && !isInclude(wholesale_record->past_drink.brand, brand)) { wholesale_record = wholesale_record->next; continue; }
        //检验口味
        if (strlen(taste) != 0 && !isInclude(wholesale_record->past_drink.taste, taste)) { wholesale_record = wholesale_record->next; continue; }
        ///创建结点
        WholesaleRecord* temp = CreatTempWholesaleRecordListNode(wholesale_record);
        tail->next = temp;
        tail = temp;
        wholesale_record = wholesale_record->next;
    }
    return head;
}
//创建临时批发记录链表结点
WholesaleRecord* CreatTempWholesaleRecordListNode(WholesaleRecord* wholesale_record) {
    WholesaleRecord* temp = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
    if (!temp) {
        printf("内存分配失败\n");
        return NULL;
    }
    strcpy(temp->order_number, wholesale_record->order_number);//订单编号
    strcpy(temp->date, wholesale_record->date);//订单日期
    strcpy(temp->user_ID, wholesale_record->user_ID);//客户账号
    strcpy(temp->past_drink.ID, wholesale_record->past_drink.ID);//酒水编号
    temp->goods_quantity = wholesale_record->goods_quantity;//批发数量
    strcpy(temp->past_drink.brand, wholesale_record->past_drink.brand);//酒水品牌
    strcpy(temp->past_drink.taste, wholesale_record->past_drink.taste);//酒水口味
    temp->past_drink.package = wholesale_record->past_drink.package;//包装种类
    strcpy(temp->past_drink.single_bottle_capacity, wholesale_record->past_drink.single_bottle_capacity);//单瓶容量
    strcpy(temp->past_drink.single_box_quantity, wholesale_record->past_drink.single_box_quantity);//单箱数量
    temp->past_drink.sale_price = wholesale_record->past_drink.sale_price;//销售价格
    //优惠
    for (int i = 0; i < 3; i++) {
        temp->discount[i].form = wholesale_record->discount[i].form; //优惠形式
        temp->discount[i].specific_1 = wholesale_record->discount->specific_1;//具体折扣
        for (int j = 0; j < 2; j++) {//具体赠品
            temp->discount[i].specific_2[j] = wholesale_record->discount[i].specific_2[j];
        }
        strcpy(temp->discount[i].reason, wholesale_record->discount[i].reason);//优惠原因
    }
    temp->goods_situation = wholesale_record->goods_situation;//订单现况
    temp->next = NULL;
    return temp;
}
//销毁临时批发记录链表（用户购物车/查询批发记录）
void DestroyTempWholesaleRecordList(WholesaleRecord* head) {
    while (head) {
        WholesaleRecord* temp = head;
        head = head->next;
        free(temp);
    }
}
//修改订单
void ManagerModifyAnWholesaleOrder(WholesaleRecord* head) {
    //查找订单
    WholesaleRecord* wholesale_record = NULL;
    while (true) {
        system("clear");
        ViewWholesaleRecords(head, NULL, 6, 0);
        wholesale_record = isOrderExist();
        if (!wholesale_record) { return; }
        if (!wholesale_record->next || !wholesale_record->next->goods_situation || wholesale_record->next->goods_situation == 5) {
            printf("未找到订单，请重新输入！\n");
            system("read");
        }
            //找到订单
        else { break; }
    }
    //查找酒水
    Drink* drink = isDrinkExist(wholesale_record->next->past_drink.ID)->next;
    //修改订单
    char discount_form[MaxSize] = { "" };
    char specific_discount[MaxSize] = { "" };
    char discount_reason[MaxSize] = { "" };
    int flag = 0;
    //设置赔偿
    while (flag != 5) {
        system("clear");
        ViewWholesaleRecords(wholesale_record, NULL, 6, 1);
        if (flag > 0) {
            if (discount_form[0] == '1') { printf("赔偿形式：折扣\n"); }
            if (discount_form[0] == '2') { printf("赔偿形式：赠品\n"); }
        }
        if (flag > 2) {
            if (discount_form[0] == '1') { printf("具体折扣：%s\n", specific_discount); }
            if (discount_form[0] == '2') { printf("赔偿箱数%s\n", specific_discount); }
        }
        if (flag > 3) { printf("赔偿原因：%s\n", discount_reason); }
        //设置赔偿形式
        while (!flag) {
            printf("请选择赔偿形式(0返回，1折扣，2赠品)：");
            fgets(discount_form, sizeof(discount_form), stdin);
            if (discount_form[0] == '1' && strlen(discount_form) == 2) { flag = 1; }
            else if (discount_form[0] == '2' && strlen(discount_form) == 2) {
                if (!drink) {
                    printf("酒水已下架！\n");
                    system("read");
                    break;
                }
                else { flag = 2; }
            }
            else if (discount_form[0] == '0' && strlen(discount_form) == 2) { return; }
            else {
                printf("非法选择，请重新输入！\n");
                system("read");
                break;
            }
        }
        //折扣
        while (flag == 1) {
            printf("请输入具体折扣(0.00~0.99)(输入0重选优惠形式)：");
            int result = isDiscountCorrect(specific_discount);
            if (!result) { flag = 0; }
            else if (result == 1) { flag = 3; }
            else { break; }
        }
        //赠品
        while (flag == 2) {
            printf("请输入赔偿箱数(输入0返回)：");
            fgets(specific_discount, sizeof(specific_discount), stdin);
            if (specific_discount[0] == '0' && strlen(specific_discount) == 2) { flag = 0; break; }
            if (strlen(specific_discount) && isNumberAllowed(specific_discount) && atoi(specific_discount) <= drink->stock_quantity) { flag = 3; break; }
            else {
                printf("箱数错误，请重新输入！\n");
                system("read");
                break;
            }
        }
        //赔偿原因
        if (flag == 3) {
            printf("请输入赔偿原因(输入0重置具体赔偿)：");
            int result = isReasonCorrect(discount_reason);
            if (!result) {
                if (discount_form[0] == '1') { flag = 1; }
                else { flag = 2; }
            }
            else  if (result == 1) { flag = 4; }
        }
        //确定设置完成
        while (flag == 4) {
            printf("是否确认赔偿(1是，2否)：");
            int result = isSure();
            if (!result) { flag = 5; }
            else if (result == 1) { flag = 3; }
            else { break; }
        }
    }
    //进行赔偿
    float old_price = wholesale_record->next->goods_quantity * wholesale_record->next->past_drink.sale_price;
    for (int i = 0; i < 2; i++) {
        old_price *= wholesale_record->next->discount[i].specific_1;
    }
    //更新批发记录
    wholesale_record->next->discount[2].form = discount_form[0] - '0';
    if (wholesale_record->next->discount[2].form == 1) {
        wholesale_record->next->discount[2].specific_1 = (specific_discount[0] - '0') + 0.1 * (float)(specific_discount[2] - '0') + 0.01 * (float)(specific_discount[3] - '0');
    }
    else {
        wholesale_record->next->discount[2].specific_2[0] = atoi(specific_discount);
    }
    strcpy(wholesale_record->next->discount[2].reason, discount_reason);
    RenewWholesaleRecordFile();
    //更新酒水信息
    drink->stock_quantity -= wholesale_record->next->discount[2].specific_2[0];
    RenewDrinkFile();
    //更新用户账户
    User* user = isUserExist(wholesale_record->next->user_ID);
    float new_price = old_price * wholesale_record->next->discount[2].specific_1;
    user->total_funding += (old_price - new_price);
    user->total_consumption -= (old_price - new_price);
    RenewUserFile();
}


/*进货部分*/
//管理员查看所有的进货记录
void ViewPurchaseRecords(PurchaseRecord* head, int type) {
    //确定链表
    PurchaseRecord* purchase_record = NULL;
    if (head) { purchase_record = head->next; }
    else { purchase_record = purchaseRecord_head->next; }
    system("clear");
    printf("订单记录\n");
    printf("************************************\n");
    while (purchase_record) {
        printf("*订单号：%s\n", purchase_record->order_number);
        printf(" 订单日期：%s\n", purchase_record->date);
        printf(" 酒水编号：%s\n", purchase_record->drink_ID);
        printf(" 酒水品牌：%s\n", purchase_record->brand);
        printf(" 酒水口味：%s\n", purchase_record->taste);
        if (purchase_record->package == 1) {
            printf(" 单瓶容量：%smL/瓶\n", purchase_record->single_bottle_capacity);
            printf(" 单箱数量：%s瓶/箱\n", purchase_record->single_box_quantity);
        }
        else if (purchase_record->package == 2) {
            printf(" 单罐容量：%smL/罐\n", purchase_record->single_bottle_capacity);
            printf(" 单箱数量：%s罐/箱\n", purchase_record->single_box_quantity);
        }
        else {
            printf(" 单盒容量：%smL/盒\n", purchase_record->single_bottle_capacity);
            printf(" 单箱数量：%s盒/箱\n", purchase_record->single_box_quantity);
        }
        printf(" 进货价格：%.2f元/箱\n", purchase_record->restocking_price);
        printf(" 进货数量：%d箱\n\n", purchase_record->goods_quantity);
        purchase_record = purchase_record->next;
        if (type == 1) { break; }
    }
    printf("************************************\n");
}
//输入查询条件
int ManagerInputPurchaseRecordConditions(char* date, char* brand, char* taste, char* package, char* capacity) {
    int flag = 0;
    while (true) {
        system("clear");
        if (flag > 0) { printf("请输入订单日期：%s\n", date); }
        if (flag > 1) { printf("请输入品牌：%s\n", brand); }
        if (flag > 2) { printf("请输入口味：%s\n", taste); }
        if (flag > 3) { printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)：%c\n", package[0]); }
        if (flag > 4) { printf("请输入单瓶容量：%s\n", capacity); }
        //订单日期
        while (!flag) {
            printf("请输入订单日期(xxxx-xx-xx)(无需直接回车)(输入0返回)：");
            fgets(date, sizeof(date), stdin);
            if (date[0] == '0' && strlen(date) == 2) { return 0; }
            else { flag = 1; }
        }
        //酒水品牌
        while (flag == 1) {
            printf("请输入品牌(无需直接回车)(输入0重选日期)：");
            fgets(brand, sizeof(brand), stdin);
            if (brand[0] == '0' && strlen(brand) == 2) { flag = 0; }
            else { flag = 2; }
        }
        //酒水口味
        while (flag == 2) {
            printf("请输入口味(无需直接回车)(输入0重选品牌)：");
            fgets(taste, sizeof(taste), stdin);
            if (taste[0] == '0' && strlen(taste) == 2) { flag = 1; }
            else { flag = 3; }
        }
        //包装种类
        while (flag == 3) {
            printf("请选择包装种类(1瓶装，2罐装，3盒装，4不限)(输入0重选口味)：");
            int result = isPackageCorrect(package, 1);
            if (!result) { flag = 2; }
            else if (result == 1) { flag = 4; }
            else { break; }
        }
        //单瓶容量
        while (flag == 4) {
            printf("请输入单瓶容量(mL)(无需直接回车)(输入0重选包装种类)：");
            fgets(capacity, sizeof(capacity), stdin);
            if (capacity[0] == '0' && strlen(capacity) == 2) { flag = 3; }
            else { flag = 5; }
        }
        //确定设置完成
        while (flag == 5) {
            printf("是否确定搜索(1是，2否)：");
            int result = isSure();
            if (!result) { return 1; }
            else if (result == 1) { flag = 4; }
            else { break; }
        }
    }
}
//建立查询进货记录链表
PurchaseRecord* CreatManagerFoundPurchaseRecordList(char* date, char* brand, char* taste, char* package, char* capacity) {
    //创建哨兵结点
    PurchaseRecord* head = (PurchaseRecord*)malloc(sizeof(PurchaseRecord));
    PurchaseRecord* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    //寻找进货记录
    PurchaseRecord* purchase_record = purchaseRecord_head->next;
    while (purchase_record) {
        //检验订单日期
        if (strlen(date) != 0 && !isInclude(purchase_record->date, date)) { purchase_record = purchase_record->next; continue; }
        //检验包装种类
        if (package[0] != '4' && purchase_record->package != (package[0] - '0')) { purchase_record = purchase_record->next; continue; }
        //检验容量
        if (strlen(capacity) != 0 && !isInputCorrect(purchase_record->single_bottle_capacity, capacity)) { purchase_record = purchase_record->next; continue; }
        //检验品牌
        if (strlen(brand) != 0 && !isInclude(purchase_record->brand, brand)) { purchase_record = purchase_record->next; continue; }
        //检验口味
        if (strlen(taste) != 0 && !isInclude(purchase_record->taste, taste)) { purchase_record = purchase_record->next; continue; }
        //创建查询进货记录链表结点
        PurchaseRecord* temp = (PurchaseRecord*)malloc(sizeof(PurchaseRecord));
        if (!temp) {
            printf("内存分配失败\n");
            return NULL;
        }
        strcpy(temp->order_number, purchase_record->order_number);//订单编号
        strcpy(temp->date, purchase_record->date);//订单日期
        strcpy(temp->drink_ID, purchase_record->drink_ID);//酒水编号
        strcpy(temp->brand, purchase_record->brand);//酒水品牌
        strcpy(temp->taste, purchase_record->taste);//酒水口味
        temp->package = purchase_record->package;//包装种类
        strcpy(temp->single_bottle_capacity, purchase_record->single_bottle_capacity);//单瓶容量
        strcpy(temp->single_box_quantity, purchase_record->single_box_quantity);//单箱数量
        temp->restocking_price = purchase_record->restocking_price;//进货价格
        temp->goods_quantity = purchase_record->goods_quantity;//进货数量
        temp->next = NULL;
        //加入链表
        tail->next = temp;
        tail = temp;
        purchase_record = purchase_record->next;
    }
    return head;
}
//销毁临时进货记录链表
void DestroyTempPurchaseRecordList(PurchaseRecord* head) {
    while (head) {
        PurchaseRecord* temp = head;
        head = head->next;
        free(temp);
    }
}
//添加订单
void AddAnPurchaseRecordOrder() {
    //输入订单信息
    char brand[MaxSize] = { "" };
    char taste[MaxSize] = { "" };
    char package[MaxSize] = { "" };
    char single_bottle_capacity[MaxSize] = { "" };
    char single_box_quantity[MaxSize] = { "" };
    char restocking_price[MaxSize] = { "" };
    char goods_quantity[MaxSize] = { "" };
    int flag = 0;
    while (flag != 8) {
        system("clear");
        if (flag > 0) { printf("请输入品牌：%s\n", brand); }
        if (flag > 1) { printf("请输入口味：%s\n", taste); }
        if (flag > 2) { printf("请选择包装种类(1瓶装，2罐装，3盒装)：%c\n", package[0]); }
        if (flag > 3) { printf("请输入单瓶容量：%smL\n", single_bottle_capacity); }
        if (flag > 4) { printf("请输入单箱数量：%s\n", single_box_quantity); }
        if (flag > 5) { printf("请输入进货价格：%s\n", restocking_price); }
        if (flag > 6) { printf("请输入进货数量：%s\n", goods_quantity); }
        //输入酒水品牌
        while (!flag) {
            printf("请输入品牌(输入0返回)：");
            int result = isBrandCorrect(brand);
            if (!result) { return; }
            else if (result == 1) { flag = 1; }
            else { break; }
        }
        //酒水口味
        while (flag == 1) {
            printf("请输入口味(输入0重选品牌)：");
            int result = isTasteCorrect(taste);
            if (!result) { flag = 0; }
            else if (result == 1) { flag = 2; }
            else { break; }
        }
        //包装种类
        while (flag == 2) {
            printf("请选择包装种类(1瓶装，2罐装，3盒装)(输入0重选口味)：");
            int result = isPackageCorrect(package, 0);
            if (!result) { flag = 1; }
            else if (result == 1) { flag = 3; }
            else { break; }
        }
        //单瓶容量
        while (flag == 3) {
            printf("请输入单瓶容量(mL)(输入0重选包装种类)：");
            int result = isSingleBottleCapacityCorrect(single_bottle_capacity);
            if (!result) { flag = 2; }
            else if (result == 1) { flag = 4; }
            else { break; }
        }
        //单箱数量
        while (flag == 4) {
            printf("请输入单箱数量(输入0重输单瓶容量)：");
            int result = isSingleBoxQuantityCorrect(single_box_quantity);
            if (!result) { flag = 3; }
            else if (result == 1) { flag = 5; }
            else { break; }
        }
        //进货价格
        while (flag == 5) {
            printf("请输入进货价格(输入0重输单箱数量)：");
            int result = isPriceCorrect(restocking_price);
            if (!result) { flag = 4; }
            else if (result == 1) { flag = 6; }
            else { break; }
        }
        //进货数量
        while (flag == 6) {
            printf("请输入进货数量(单次小于十万)(输入0重输进货价格)：");
            int result = isGoodsQuantityCorrect(goods_quantity);
            if (!result) { flag = 5; }
            else if (result == 1) { flag = 7; }
            else { break; }
        }
        //确定设置完成
        while (flag == 7) {
            printf("是否确定入库(1是，2否)：");
            int result = isSure();
            if (!result) { flag = 8; }
            else if (result == 1) { flag = 6; }
            else { break; }
        }
    }
    //创建新订单结点
    PurchaseRecord* temp = (PurchaseRecord*)malloc(sizeof(PurchaseRecord));
    if (!temp) {
        printf("内存分配失败\n");
        return;
    }
    //订单编号
    if (!purchaseRecord_head->next) { strcpy(temp->order_number, "0000000001"); }
    else { strcpy(temp->order_number, BuildID(purchaseRecord_head->next->order_number)); }
    //订单日期
    time_t current_time;
    struct tm* time_info;
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(temp->date, 20, "%Y-%m-%d_%H:%M:%S", time_info);
    strcpy(temp->drink_ID, "0000000000");//酒水编号
    strcpy(temp->brand, brand);//酒水品牌
    strcpy(temp->taste, taste);//酒水口味
    temp->package = atoi(package);//包装种类
    strcpy(temp->single_bottle_capacity, single_bottle_capacity);//单瓶容量
    strcpy(temp->single_box_quantity, single_box_quantity);//单箱数量
    temp->restocking_price = atoi(restocking_price);//进货价格
    temp->goods_quantity = atoi(goods_quantity);//进货数量
    temp->next = NULL;
    //更新酒水
    //查找酒水结点是否已存在
    Drink* drink = drink_head->next;
    while (drink) {
        if (!isInputCorrect(drink->brand, brand)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->taste, taste)) { drink = drink->next; continue; }
        if (drink->package != atoi(package)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_bottle_capacity, single_bottle_capacity)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_box_quantity, single_box_quantity)) { drink = drink->next; continue; }
        break;
    }
    //结点已存在则更新此结点
    if (drink) {
        if (drink->stock_quantity + temp->goods_quantity > 1000000) {
            free(temp);
            printf("该酒水库存已满，入库失败！\n");
            system("read");
            return;
        }
        drink->stock_quantity += temp->goods_quantity;
        strcpy(temp->drink_ID, drink->ID);
    }
        //结点不存在则新建酒水结点
    else { AddDrink(temp); }
    //加入链表
    temp->next = purchaseRecord_head->next;
    purchaseRecord_head->next = temp;
    RenewPurchaseRecordFile();
    //更新管理员信息
    manager->fund -= temp->goods_quantity * temp->restocking_price;
    RenewManagerFile();
    //订单创建成功
    printf("订单创建成功！\n");
    system("read");
}
//添加酒水
void AddDrink(PurchaseRecord* purchase_record) {
    //创建新酒水链表结点
    Drink* temp = (Drink*)malloc(sizeof(Drink));
    if (!temp) {
        printf("内存分配失败\n");
        return;
    }
    else {
        strcpy(temp->brand, purchase_record->brand);//酒水品牌
        strcpy(temp->taste, purchase_record->taste);//酒水口味
        temp->package = purchase_record->package;//包装种类
        strcpy(temp->single_bottle_capacity, purchase_record->single_bottle_capacity);//单瓶容量
        strcpy(temp->single_box_quantity, purchase_record->single_box_quantity);//单箱数量
        temp->restocking_price = purchase_record->restocking_price;//进货价格
        temp->stock_quantity = purchase_record->goods_quantity;//库存数量
        temp->activity.form = 0; //优惠形式
        temp->activity.specific_1 = 1;//具体折扣
        for (int i = 0; i < 2; i++) {//具体赠品
            temp->activity.specific_2[i] = 0;
        }
        strcpy(temp->activity.reason, "无");//优惠原因
        for (int i = 0; i < 2; i++) { //活动时间
            strcpy(temp->activity.date[i], "2000.01.01_00:00:00");
        }
        temp->next = NULL;
    }
    //销售价格
    while (true) {
        system("clear");
        printf("品牌：%s\n", purchase_record->brand);
        printf("口味：%s\n", purchase_record->taste);
        printf("包装种类(1瓶装，2罐装，3盒装)：%d\n", purchase_record->package);
        printf("单瓶容量：%smL\n", purchase_record->single_bottle_capacity);
        printf("单箱数量：%s\n", purchase_record->single_box_quantity);
        printf("进货数量：%d\n", purchase_record->goods_quantity);
        printf("销售价格：");
        char sale_price[MaxSize] = { "" };
        fgets(sale_price, sizeof(sale_price), stdin);
        if (strlen(sale_price) && strlen(sale_price) < 9 && isNumberAllowed(sale_price)) { temp->sale_price = atoi(sale_price); break; }
        else {
            printf("价格错误，请重新输入！\n");
            system("read");
        }
    }
    //创建新酒水编号
    //新酒水编号
    char brand_ID[5] = { "0001" };
    char taste_ID[4] = { "001" };
    char package_ID[2] = { "1" };
    char bottle_capacity_ID[2] = { "1" };
    char box_quantity_ID[2] = { "1" };
    //酒水编号
    char pre_brand_ID[5] = { "" };
    char pre_taste_ID[4] = { "" };
    char pre_package_ID[2] = { "" };
    char pre_bottle_capacity_ID[2] = { "" };
    char pre_box_quantity_ID[2] = { "" };
    //查找有无相同品牌
    Drink* drink = drink_head;
    while (drink->next) {
        if (isInputCorrect(drink->next->brand, purchase_record->brand)) { break; }
        drink = drink->next;
    }
    int flag = 0;
    //不存在相同品牌的酒水
    if (!drink->next) {
        if (drink_head->next) {
            for (int i = 0; i < 4; i++) {
                pre_brand_ID[i] = drink->ID[i];
            }
            pre_brand_ID[4] = '\0';
            strcpy(brand_ID, BuildID(pre_brand_ID));
        }
        for (int i = 0; i < 4; i++) { temp->ID[i] = brand_ID[i]; }
        for (int i = 0; i < 3; i++) { temp->ID[i + 4] = taste_ID[i]; }
        temp->ID[7] = package_ID[0];
        temp->ID[8] = bottle_capacity_ID[0];
        temp->ID[9] = box_quantity_ID[0];
        temp->ID[10] = '\0';
    }
        //存在相同品牌的酒水
    else {
        for (int i = 0; i < 4; i++) {
            temp->ID[i] = drink->next->ID[i];
        }
        flag = 1;
    }
    //存在相同品牌的酒水时，查找有无相同口味
    if (flag == 1) {
        while (drink->next) {
            if (isInputCorrect(drink->next->brand, purchase_record->brand) && isInputCorrect(drink->next->taste, purchase_record->taste)) { break; }
            drink = drink->next;
        }
        //不存在相同口味的酒水
        if (!drink->next) {
            for (int i = 0; i < 3; i++) {
                pre_taste_ID[i] = drink->ID[i + 4];
            }
            pre_taste_ID[3] = '\0';
            strcpy(taste_ID, BuildID(pre_taste_ID));
            for (int i = 0; i < 3; i++) { temp->ID[i + 4] = taste_ID[i]; }
            temp->ID[7] = package_ID[0];
            temp->ID[8] = bottle_capacity_ID[0];
            temp->ID[9] = box_quantity_ID[0];
            temp->ID[10] = '\0';
        }
            //存在相同口味的酒水
        else {
            for (int i = 0; i < 3; i++) {
                temp->ID[i + 4] = drink->next->ID[i + 4];
            }
            flag = 2;
        }
    }
    //存在相同品牌、相同口味的酒水时，查找有无相同包装
    if (flag == 2) {
        while (drink->next) {
            if (isInputCorrect(drink->next->brand, purchase_record->brand) && isInputCorrect(drink->next->taste, purchase_record->taste) && drink->next->package == purchase_record->package) { break; }
            drink = drink->next;
        }
        //不存在相同包装的酒水
        if (!drink->next) {
            pre_package_ID[0] = drink->ID[7];
            pre_package_ID[1] = '\0';
            strcpy(package_ID, BuildID(pre_package_ID));
            temp->ID[7] = package_ID[0];
            temp->ID[8] = bottle_capacity_ID[0];
            temp->ID[9] = box_quantity_ID[0];
            temp->ID[10] = '\0';
        }
            //存在相同包装的酒水
        else {
            temp->ID[7] = drink->next->ID[7];
            flag = 3;
        }
    }
    //存在相同品牌、相同口味、相同包装的酒水时，查找有无相同单瓶容量
    if (flag == 3) {
        while (drink->next) {
            if (isInputCorrect(drink->next->brand, purchase_record->brand) && isInputCorrect(drink->next->taste, purchase_record->taste) && drink->next->package == purchase_record->package && isInputCorrect(drink->next->single_bottle_capacity, purchase_record->single_bottle_capacity)) { break; }
            drink = drink->next;
        }
        //不存在相同单瓶容量的酒水
        if (!drink->next) {
            pre_bottle_capacity_ID[0] = drink->ID[8];
            pre_bottle_capacity_ID[1] = '\0';
            strcpy(bottle_capacity_ID, BuildID(pre_bottle_capacity_ID));
            temp->ID[8] = bottle_capacity_ID[0];
            temp->ID[9] = box_quantity_ID[0];
            temp->ID[10] = '\0';
        }
            //存在相同单瓶容量的酒水
        else {
            temp->ID[8] = drink->next->ID[8];
            pre_box_quantity_ID[0] = drink->next->ID[9];
            pre_box_quantity_ID[1] = '\0';
            strcpy(box_quantity_ID, BuildID(pre_box_quantity_ID));
            temp->ID[9] = box_quantity_ID[0];
            temp->ID[10] = '\0';
        }
    }
    //加入链表
    strcpy(purchase_record->drink_ID, temp->ID);
    temp->next = drink->next;
    drink->next = temp;
    RenewDrinkFile();
}
///修改订单
//修改进货记录日期
void ModifyPurchaseRecordDate(PurchaseRecord* purchase_record) {
    //输入信息
    char date[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入进货日期(xxxx-xx-xx_xx:xx:xx)(输入0返回)：");
        fgets(date, sizeof(date), stdin);
        //检测是否返回
        if (date[0] == '0' && strlen(date) == 2) { return; }
        //输入正确，则修改信息
        if (isTimeAllowed(date)) { break; }
            //输入错误，则重新输入
        else {
            printf("日期错误，请重新输入！\n");
            system("read");
        }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将进货日期改为：%s(1是，2否)", date);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
        else { break; }
    }
    //更新信息
    strcpy(purchase_record->next->date, date);
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
//修改进货酒水品牌
void ModifyPurchaseRecordBrand(PurchaseRecord* purchase_record) {
    //查找订单对应酒水
    Drink* drink = isDrinkExist(purchase_record->next->drink_ID);
    if (!drink->next) {
        printf("酒水已下架！\n");
        system("pasue");
        return;
    }
    //输入信息
    char brand[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入品牌(输入0返回)：");
        int result = isBrandCorrect(brand);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将品牌改为：%s(1是，2否)", brand);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    drink->next->stock_quantity -= purchase_record->next->goods_quantity;
    strcpy(purchase_record->next->brand, brand);
    drink = drink_head->next;
    //查找更改品牌后的酒水结点是否已存在
    while (drink) {
        if (!isInputCorrect(drink->brand, purchase_record->next->brand)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->taste, purchase_record->next->taste)) { drink = drink->next; continue; }
        if (drink->package != purchase_record->next->package) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_bottle_capacity, purchase_record->next->single_bottle_capacity)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_box_quantity, purchase_record->next->single_box_quantity)) { drink = drink->next; continue; }
        break;
    }
    //结点已存在则更新此结点
    if (drink) {
        drink->stock_quantity += purchase_record->next->goods_quantity;
        strcpy(purchase_record->next->drink_ID, drink->ID);
    }
        //结点不存在则新建酒水结点
    else { AddDrink(purchase_record->next); }
    //修改成功
    RenewDrinkFile();
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
//修改进货酒水口味
void ModifyPurchaseRecordTaste(PurchaseRecord* purchase_record) {
    //查找订单对应酒水
    Drink* drink = isDrinkExist(purchase_record->next->drink_ID);
    if (!drink->next) {
        printf("酒水已下架！\n");
        system("pasue");
        return;
    }
    //输入信息
    char taste[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入口味(输入0返回)：");
        int result = isTasteCorrect(taste);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将口味改为：%s(1是，2否)", taste);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    drink->next->stock_quantity -= purchase_record->next->goods_quantity;
    strcpy(purchase_record->next->taste, taste);
    drink = drink_head->next;
    //查找更改口味后的酒水结点是否已存在
    while (drink) {
        if (!isInputCorrect(drink->brand, purchase_record->next->brand)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->taste, purchase_record->next->taste)) { drink = drink->next; continue; }
        if (drink->package != purchase_record->next->package) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_bottle_capacity, purchase_record->next->single_bottle_capacity)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_box_quantity, purchase_record->next->single_box_quantity)) { drink = drink->next; continue; }
        break;
    }
    //结点已存在则更新此结点
    if (drink) {
        drink->stock_quantity += purchase_record->next->goods_quantity;
        strcpy(purchase_record->next->drink_ID, drink->ID);
    }
        //结点不存在则新建酒水结点
    else { AddDrink(purchase_record->next); }
    //修改成功
    RenewDrinkFile();
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
//修改进货酒水包装
void ModifyPurchaseRecordPackage(PurchaseRecord* purchase_record) {
    //查找订单对应酒水
    Drink* drink = isDrinkExist(purchase_record->next->drink_ID);
    if (!drink->next) {
        printf("酒水已下架！\n");
        system("pasue");
        return;
    }
    //输入信息
    char package[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入包装种类(1瓶装，2罐装，3盒装)(输入0返回)：");
        int result = isPackageCorrect(package, 0);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将包装改为：%c(1瓶装，2罐装，3盒装)(1是，2否)", package[0]);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    drink->next->stock_quantity -= purchase_record->next->goods_quantity;
    purchase_record->next->package = package[0] - '0';
    drink = drink_head->next;
    //查找更改口味后的酒水结点是否已存在
    while (drink) {
        if (!isInputCorrect(drink->brand, purchase_record->next->brand)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->taste, purchase_record->next->taste)) { drink = drink->next; continue; }
        if (drink->package != purchase_record->next->package) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_bottle_capacity, purchase_record->next->single_bottle_capacity)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_box_quantity, purchase_record->next->single_box_quantity)) { drink = drink->next; continue; }
        break;
    }
    //结点已存在则更新此结点
    if (drink) {
        drink->stock_quantity += purchase_record->next->goods_quantity;
        strcpy(purchase_record->next->drink_ID, drink->ID);
    }
        //结点不存在则新建酒水结点
    else { AddDrink(purchase_record->next); }
    //修改成功
    RenewDrinkFile();
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
//修改进货酒水单瓶容量
void ModifyPurchaseRecordBottleCapacity(PurchaseRecord* purchase_record) {
    //查找订单对应酒水
    Drink* drink = isDrinkExist(purchase_record->next->drink_ID);
    if (!drink->next) {
        printf("酒水已下架！\n");
        system("pasue");
        return;
    }
    //输入信息
    char capacity[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入单瓶容量(mL)(输入0返回)：");
        int result = isSingleBottleCapacityCorrect(capacity);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将容量改为：%smL(1是，2否)", capacity);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    drink->next->stock_quantity -= purchase_record->next->goods_quantity;
    strcpy(purchase_record->next->single_bottle_capacity, capacity);
    drink = drink_head->next;
    //查找更改口味后的酒水结点是否已存在
    while (drink) {
        if (!isInputCorrect(drink->brand, purchase_record->next->brand)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->taste, purchase_record->next->taste)) { drink = drink->next; continue; }
        if (drink->package != purchase_record->next->package) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_bottle_capacity, purchase_record->next->single_bottle_capacity)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_box_quantity, purchase_record->next->single_box_quantity)) { drink = drink->next; continue; }
        break;
    }
    //结点已存在则更新此结点
    if (drink) {
        drink->stock_quantity += purchase_record->next->goods_quantity;
        strcpy(purchase_record->next->drink_ID, drink->ID);
    }
        //结点不存在则新建酒水结点
    else { AddDrink(purchase_record->next); }
    //修改成功
    RenewDrinkFile();
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
//修改进货酒水单箱数量
void ModifyPurchaseRecordBoxQuantity(PurchaseRecord* purchase_record) {
    //查找订单对应酒水
    Drink* drink = isDrinkExist(purchase_record->next->drink_ID);
    if (!drink->next) {
        printf("酒水已下架！\n");
        system("pasue");
        return;
    }
    //输入信息
    char quantity[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入单箱数量(输入0返回)：");
        int result = isSingleBoxQuantityCorrect(quantity);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将单箱数量改为：%s(1是，2否)", quantity);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    drink->next->stock_quantity -= purchase_record->next->goods_quantity;
    strcpy(purchase_record->next->single_box_quantity, quantity);
    drink = drink_head->next;
    //查找更改口味后的酒水结点是否已存在
    while (drink) {
        if (!isInputCorrect(drink->brand, purchase_record->next->brand)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->taste, purchase_record->next->taste)) { drink = drink->next; continue; }
        if (drink->package != purchase_record->next->package) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_bottle_capacity, purchase_record->next->single_bottle_capacity)) { drink = drink->next; continue; }
        if (!isInputCorrect(drink->single_box_quantity, purchase_record->next->single_box_quantity)) { drink = drink->next; continue; }
        break;
    }
    //结点已存在则更新此结点
    if (drink) {
        drink->stock_quantity += purchase_record->next->goods_quantity;
        strcpy(purchase_record->next->drink_ID, drink->ID);
    }
        //结点不存在则新建酒水结点
    else { AddDrink(purchase_record->next); }
    //修改成功
    RenewDrinkFile();
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
//修改酒水进货价格
void ModifyPurchaseRecordRestockingPrice(PurchaseRecord* purchase_record) {
    //输入信息
    char price[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入进货价格(输入0返回)：");
        int result = isPriceCorrect(price);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将进货价格改为：%s(1是，2否)", price);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    manager->fund -= purchase_record->next->restocking_price * purchase_record->next->goods_quantity;
    purchase_record->next->restocking_price = atoi(price);
    manager->fund += purchase_record->next->restocking_price * purchase_record->next->goods_quantity;
    RenewPurchaseRecordFile();
    RenewManagerFile();
    printf("修改成功！\n");
    system("read");
}
//修改酒水进货数量
void ModifyPurchaseRecordGoodsQuantity(PurchaseRecord* purchase_record) {
    //查找订单对应酒水
    Drink* drink = isDrinkExist(purchase_record->next->drink_ID);
    if (!drink->next) {
        printf("酒水已下架！\n");
        system("pasue");
        return;
    }
    //输入信息
    char quantity[MaxSize] = { "" };
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("请输入进货数量(单次小于十万)(输入0返回)：");
        int result = isGoodsQuantityCorrect(quantity);
        if (!result) { return; }
        else if (result == 1) { break; }
    }
    //最后确认
    while (true) {
        system("clear");
        ViewPurchaseRecords(purchase_record, 1);
        printf("是否确认将进货数量改为：%s箱(1是，2否)", quantity);
        int result = isSure();
        if (!result) { break; }
        else if (result == 1) { return; }
    }
    //更新信息
    manager->fund -= purchase_record->next->restocking_price * purchase_record->next->goods_quantity;
    drink->next->stock_quantity -= purchase_record->next->goods_quantity;
    purchase_record->next->goods_quantity = atoi(quantity);
    manager->fund += purchase_record->next->restocking_price * purchase_record->next->goods_quantity;
    drink->next->stock_quantity += purchase_record->next->goods_quantity;
    //修改成功
    RenewManagerFile();
    RenewDrinkFile();
    RenewPurchaseRecordFile();
    printf("修改成功！\n");
    system("read");
}
