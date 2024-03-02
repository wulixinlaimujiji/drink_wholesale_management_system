#include "public.h"
#include "manager.h"
#include "user.h"

//��������Ա��¼
Manager *manager;
//�����û�����
User *user_head;
//������ˮ����
Drink *drink_head;
//����������¼����
WholesaleRecord *wholesaleRecord_head;
//����������¼����
PurchaseRecord *purchaseRecord_head;

/*** ��ʼҳ�� ***/
//ϵͳ��ʼ��
void SystemInitialization();

//��¼ҳ��
void LoginMenu();
/*** �û�ҳ�� ***/
///�û���¼ҳ��
void UserLoginMenu();

///�û�����ҳ��
void UserMenu(User *user);

//�û�������Ϣҳ��
void UserInformationMenu(User *user);

//�û���Ϣ�޸�ҳ��
void UserModifyInformationMenu(User *user);

//�鿴��ˮҳ��
void UserViewAvailableDrinksMenu(User *user);

//�û����ﳵҳ��
void UserViewShoppingCartMenu(User *user);

//�û�������¼ҳ��
void UserViewWholesaleRecordMenu(User *user);
/*** ����Աҳ�� ***/
///����Ա��¼ҳ��
void ManagerLoginMenu();

///����Ա����ҳ��
void ManagerMenu();

//����Ա��Ϣҳ��
void ManagerInformationMenu();

//�û���Ϣҳ��
void UsersInformationMenu();

//�����û�ҳ��
void SearchUserMenu();

//�鿴��ˮҳ��
void ManagerViewAvailableDrinksMenu();

//�޸ľ�ˮ��Ϣҳ��
void ModifyDrinkInformationMenu(Drink *found_drink_head);

//����Ա�鿴������Ϣҳ��
void ManagerViewNewMessageMenu();

//�鿴�µ���Ϣҳ��
void ManagerViewOrderInformationMenu();

//�鿴�˵���Ϣҳ��
void ManagerViewReturnInformationMenu();

//����Ա������¼ҳ��
void ManagerViewWholesaleRecordMenu();

//����Ա������¼ҳ��
void ManagerViewPurchaseRecordMenu();

//����Ա������¼�޸�ҳ��
void ManagerModifyPurchaseRecordMenu(PurchaseRecord *head);

int main(void) {
    SystemInitialization();
    LoginMenu();
    return 0;
}

/*** ��ʼҳ�� ***/
//ϵͳ��ʼ��
void SystemInitialization() {
    manager = CreatManager();
    user_head = CreatUserList();
    drink_head = CreatDrinkList();
    wholesaleRecord_head = CreatWholesaleRecordList();
    purchaseRecord_head = CreatPurchaseRecordList();
}

//��¼ҳ��
void LoginMenu() {
    while (true) {
        system("cls");
        printf("��ӭ�����ˮ����ϵͳ��\n");
        printf("*****************************\n");
        printf("********1������Ա��¼********\n");
        printf("********2���ͻ���¼**********\n");
        printf("********0���˳�ϵͳ**********\n");
        printf("*****************************\n");
        printf("����ѡ���ǣ�");
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //ѡ�����Ա��ݵ�¼
        if (select[0] == '1' && strlen(select) == 2) { ManagerLoginMenu(); }
            //ѡ���û���ݵ�¼
        else if (select[0] == '2' && strlen(select) == 2) { UserLoginMenu(); }
            //�˳�ϵͳ
        else if (select[0] == '0' && strlen(select) == 2) { return; }
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}
/*** �û�ҳ�� ***/
///�û���¼ҳ��
void UserLoginMenu() {
    while (true) {
        system("cls");
        printf("��ӭ����ͻ�ģʽ��\n");
        printf("***************************\n");
        printf("*********1����¼***********\n");
        printf("*********2��ע��***********\n");
        printf("*********3����������*******\n");
        printf("*********0������***********\n");
        printf("***************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //ѡ���¼�˺�
        if (select[0] == '1' && strlen(select) == 2) {
            User *user = UserLogin(user_head);
            //��¼�ɹ��������û�����ҳ��
            if (user) { UserMenu(user); }
        }
            //ѡ��ע���˺�
        else if (select[0] == '2' && strlen(select) == 2) { UserSignUp(); }
            //ѡ����������
        else if (select[0] == '3' && strlen(select) == 2) { ForgotUserPassword(); }
            //ѡ�񷵻�
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

///�û�����ҳ��
void UserMenu(User *user) {
    while (true) {
        //����ѡ��ҳ��
        system("cls");
        printf("*******************************\n");
        printf("********1���鿴������Ϣ********\n");
        printf("********2���鿴���۾�ˮ********\n");
        printf("********3���鿴���ﳵ**********\n");
        printf("********4���鿴����************\n");
        printf("********0���˳���¼************\n");
        printf("*******************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�鿴������Ϣ
        if (select[0] == '1' && strlen(select) == 2) { UserInformationMenu(user); }
            //�鿴���۾�ˮ
        else if (select[0] == '2' && strlen(select) == 2) { UserViewAvailableDrinksMenu(user); }
            //�鿴���ﳵ
        else if (select[0] == '3' && strlen(select) == 2) { UserViewShoppingCartMenu(user); }
            //�鿴������¼
        else if (select[0] == '4' && strlen(select) == 2) { UserViewWholesaleRecordMenu(user); }
            //�˳���¼
        else if (select[0] == '0' && strlen(select) == 2) {
            printf("�˳��ɹ�����ӭ�´�ʹ�ã�\n");
            system("read");
            return;
        }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�û�������Ϣҳ��
void UserInformationMenu(User *user) {
    while (true) {
        //�û��鿴������Ϣ
        system("cls");
        UserInformation(user, 1);
        //��ز���
        printf("\n����\n");
        printf("***************************\n");
        printf("********1���޸���Ϣ********\n");
        printf("********2���޸�����********\n");
        printf("********3����ֵ���********\n");
        printf("********0���˳�����********\n");
        printf("***************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //ѡ���޸ĵ���Ϣ
        if (select[0] == '1' && strlen(select) == 2) { UserModifyInformationMenu(user); }
            //�޸�����
        else if (select[0] == '2' && strlen(select) == 2) { ModifyUserPassword(user); }
            //��ֵ���
        else if (select[0] == '3' && strlen(select) == 2) { UserRecharge(user); }
            //�˳�������Ϣ����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�û���Ϣ�޸�ҳ��
void UserModifyInformationMenu(User *user) {
    while (true) {
        //�û����޸���Ϣ
        system("cls");
        printf("********************************\n");
        printf("***** 1���������ƣ�%s\n", user->name);
        printf("***** 2���ջ���ַ��%s\n", user->address);
        printf("***** 3����ϵ��ʽ��%s\n", user->Tel);
        printf("***** 0�����ظ�����Ϣ����\n");
        printf("********************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�޸���������
        if (select[0] == '1' && strlen(select) == 2) { ModifyUserName(user); }
            //�޸������ַ
        else if (select[0] == '2' && strlen(select) == 2) { ModifyUserAddress(user); }
            //�޸���ϵ��ʽ
        else if (select[0] == '3' && strlen(select) == 2) { ModifyUserTel(user); }
            //���ظ�����Ϣ����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�鿴��ˮҳ��
void UserViewAvailableDrinksMenu(User *user) {
    char brand[MaxSize] = {""};
    char taste[MaxSize] = {""};
    char package[MaxSize] = {""};
    char capacity[MaxSize] = {""};
    char activity[MaxSize] = {""};
    Drink *found_drink_head = NULL;    //������ѯ��ˮ����
    while (true) {
        //����
        system("cls");
        if (!found_drink_head) {
            //�û��鿴ȫ�����۾�ˮ
            ViewAvailableDrinks(found_drink_head, 1, 0);
            //��ز���
            printf("\n����\n");
            printf("*********************************\n");
            printf("******1��ѡ���ˮ���빺�ﳵ******\n");
            printf("******2��ѡ���ˮֱ���µ�********\n");
            printf("******3��������������ˮ**********\n");
            printf("******0���˳���ˮ����************\n");
            printf("*********************************\n");
            printf("����ѡ���ǣ�");
        } else {
            //�û��鿴�����������۾�ˮ
            printf("��������\n");
            printf("**************************************\n");
            printf("Ʒ�ƣ�%s\n", brand);
            printf("��ζ��%s\n", taste);
            printf("��װ����(1ƿװ��2��װ��3��װ��4����)��%c\n", package[0]);
            printf("��ƿ������%smL\n", capacity);
            printf("�Żݻ(1�ۿۣ�2��Ʒ��3����)��%c\n", activity[0]);
            printf("**************************************\n");
            ViewAvailableDrinks(found_drink_head, 1, 0);
            //��ز���
            printf("\n����\n");
            printf("*********************************\n");
            printf("******1��ѡ���ˮ���빺�ﳵ******\n");
            printf("******2��ѡ���ˮֱ���µ�********\n");
            printf("******3��������������ˮ**********\n");
            printf("******0���˳���������************\n");
            printf("*********************************\n");
            printf("����ѡ���ǣ�");
        }
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //ѡ���ˮ���빺�ﳵ
        if (select[0] == '1' && strlen(select) == 2) { AddDrinkToTheCart(user, found_drink_head); }
            //ѡ���ˮֱ���µ�
        else if (select[0] == '2' && strlen(select) == 2) { PayForDrink(user, found_drink_head); }
            //������������ˮ����ҳ��
        else if (select[0] == '3' && strlen(select) == 2) {
            //���ٲ�ѯ��ˮ����
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
            //�����ѯ����
            if (InputDrinkConditions(brand, taste, package, capacity, activity) == 1) {
                //������ѯ��ˮ����
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //������һ����
        else if (select[0] == '0' && strlen(select) == 2) {
            if (!found_drink_head) { return; }
            else {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
        }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�û����ﳵҳ��
void UserViewShoppingCartMenu(User *user) {
    while (true) {
        //�������ﳵ����
        WholesaleRecord *cart_head = CreatUserShoppingCartList(user);
        //�鿴�û����ﳵ
        system("cls");
        ViewUserShoppingCart(user, cart_head, 0);
        printf("\n����\n");
        printf("*******************************\n");
        printf("********1���޸Ķ���************\n");
        printf("********2��ѡ�񶩵��µ�********\n");
        printf("********3��ȫѡ�µ�************\n");
        printf("********4��ѡ�񶩵�ɾ��********\n");
        printf("********5����չ��ﳵ**********\n");
        printf("********0���˳����ﳵ**********\n");
        printf("*******************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�޸Ķ���
        if (select[0] == '1' && strlen(select) == 2) { UserModifyAnOrder(user, cart_head); }
            //ѡ�񶩵��µ�
        else if (select[0] == '2' && strlen(select) == 2) { PayForAnOrder(user, cart_head); }
            //ȫѡ�µ�
        else if (select[0] == '3' && strlen(select) == 2) { PayForAllOrder(user, cart_head); }
            //ѡ�񶩵�ɾ��
        else if (select[0] == '4' && strlen(select) == 2) { DeleteAnOrder(user, cart_head); }
            //��չ��ﳵ
        else if (select[0] == '5' && strlen(select) == 2) { clsShoppingCart(user, cart_head); }
            //�˳����ﳵ
        else if (select[0] == '0' && strlen(select) == 2) {
            //�����û����ﳵ����
            DestroyTempWholesaleRecordList(cart_head);
            cart_head = NULL;
            return;
        }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
        //�����û����ﳵ����
        DestroyTempWholesaleRecordList(cart_head);
        cart_head = NULL;
    }
}

//�û�������¼ҳ��
void UserViewWholesaleRecordMenu(User *user) {
    char date[MaxSize] = {""};
    char situation[MaxSize] = {""};
    char brand[MaxSize] = {""};
    char taste[MaxSize] = {""};
    char package[MaxSize] = {""};
    char capacity[MaxSize] = {""};
    WholesaleRecord *found_wholesaleRecord_head = NULL;    //������ѯ������¼����
    while (true) {
        system("cls");
        if (!found_wholesaleRecord_head) {
            //�û��鿴���е�������¼
            ViewWholesaleRecords(found_wholesaleRecord_head, user, 6, 0);
            //��ز���
            printf("\n����\n");
            printf("*******************************\n");
            printf("********1�������˻�************\n");
            printf("********2�����Ҷ���************\n");
            printf("********0���˳�ҳ��************\n");
            printf("*******************************\n");
            printf("����ѡ���ǣ�");
        } else {
            //�û��鿴��������������¼
            printf("��������\n");
            printf("**************************************\n");
            printf("�������ڣ�%s\n", date);
            printf("�����ֿ�(1���µ���2�����У�3�ѵ�����4�����˻���5���˻���6����)��%c\n", situation[0]);
            printf("Ʒ�ƣ�%s\n", brand);
            printf("��ζ��%s\n", taste);
            printf("��װ����(1ƿװ��2��װ��3��װ��4����)��%c\n", package[0]);
            printf("��ƿ������%sml\n", capacity);
            printf("**************************************\n");
            ViewWholesaleRecords(found_wholesaleRecord_head, user, 6, 0);
            //��ز���
            printf("\n����\n");
            printf("*******************************\n");
            printf("********1�������˻�************\n");
            printf("********2�����Ҷ���************\n");
            printf("********0���˳�����ҳ��********\n");
            printf("*******************************\n");
            printf("����ѡ���ǣ�");
        }
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�����˻�
        if (select[0] == '1' && strlen(select) == 2) { UserApplicationForReturn(user, found_wholesaleRecord_head); }
            //���Ҷ���
        else if (select[0] == '2' && strlen(select) == 2) {
            //���ٲ�ѯ������¼����
            if (found_wholesaleRecord_head) {
                DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                found_wholesaleRecord_head = NULL;
            }
            //�����ѯ����
            if (UserInputWholesaleRecordConditions(date, situation, brand, taste, package, capacity) == 1) {
                //������ѯ������¼����
                found_wholesaleRecord_head = CreatUserFoundWholesaleRecordList(date, situation, brand, taste, package,
                                                                               capacity);
            }
        }
            //������һ����
        else if (select[0] == '0' && strlen(select) == 2) {
            if (!found_wholesaleRecord_head) { return; }
            else {
                DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                found_wholesaleRecord_head = NULL;
            }
        }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}
/*** ����Աҳ�� ***/
///����Ա��¼ҳ��
void ManagerLoginMenu() {
    while (true) {
        system("cls");
        printf("��ӭ�������Աģʽ��\n");
        printf("***************************\n");
        printf("*********1����¼***********\n");
        printf("*********2����������*******\n");
        printf("*********0������***********\n");
        printf("***************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //ѡ���¼�˺�
        if (select[0] == '1' && strlen(select) == 2) {
            //��¼�ɹ����������Ա����ҳ��
            if (ManagerLogin()) { ManagerMenu(); }
        }
            //ѡ����������
        else if (select[0] == '2' && strlen(select) == 2) { ForgotManagerPassword(); }
            //ѡ�񷵻�
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

///����Ա����ҳ��
void ManagerMenu() {
    while (true) {
        //����ѡ��ҳ��
        system("cls");
        printf("*******************************\n");
        printf("********1���鿴����Ա��Ϣ******\n");
        printf("********2���鿴�û���Ϣ********\n");
        printf("********3���鿴���۾�ˮ********\n");
        printf("********4���鿴������Ϣ********\n");
        printf("********5���鿴��������********\n");
        printf("********6���鿴��������********\n");
        printf("********0���˳���¼************\n");
        printf("*******************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�鿴����Ա��Ϣ
        if (select[0] == '1' && strlen(select) == 2) { ManagerInformationMenu(); }
            //�鿴�û���Ϣ
        else if (select[0] == '2' && strlen(select) == 2) { UsersInformationMenu(); }
            //�鿴���۾�ˮ
        else if (select[0] == '3' && strlen(select) == 2) { ManagerViewAvailableDrinksMenu(); }
            //�鿴������Ϣ
        else if (select[0] == '4' && strlen(select) == 2) { ManagerViewNewMessageMenu(); }
            //�鿴������¼
        else if (select[0] == '5' && strlen(select) == 2) { ManagerViewWholesaleRecordMenu(); }
            //�鿴������¼
        else if (select[0] == '6' && strlen(select) == 2) { ManagerViewPurchaseRecordMenu(); }
            //�˳���¼
        else if (select[0] == '0' && strlen(select) == 2) {
            printf("�˳��ɹ�����ӭ�´�ʹ�ã�\n");
            system("read");
            return;
        }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//����Ա��Ϣҳ��
void ManagerInformationMenu() {
    while (true) {
        //�鿴����Ա��Ϣ
        system("cls");
        ManagerInformation();
        //��ز���
        printf("\n����\n");
        printf("***************************\n");
        printf("*******1���޸���ϵ��ʽ*****\n");
        printf("*******2���޸�����*********\n");
        printf("*******0���˳�����*********\n");
        printf("***************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�޸���ϵ��ʽ
        if (select[0] == '1' && strlen(select) == 2) { ModifyManagerTel(); }
            //�޸�����
        else if (select[0] == '2' && strlen(select) == 2) { ModifyManagerPassword(); }
            //�˳�����Ա��Ϣ����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�û���Ϣҳ��
void UsersInformationMenu() {
    while (true) {
        system("cls");
        UserInformation(NULL, 0);
        //��ز���
        printf("\n����\n");
        printf("***************************\n");
        printf("********1�������û�********\n");
        printf("********0���˳�����********\n");
        printf("***************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�����û�
        if (select[0] == '1' && strlen(select) == 2) { SearchUserMenu(); }
            //�˳�����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�����û�ҳ��
void SearchUserMenu() {
    //�����˺�
    User *user = NULL;
    while (true) {
        system("cls");
        //�����˺Ż���ϵ��ʽ
        printf("�������˺Ż���ϵ��ʽ(����0����)��");
        char input[MaxSize] = {""};
        fgets(input, sizeof(input), stdin);
        //����Ƿ񷵻�
        if (input[0] == '0' && strlen(input) == 2) { return; }
        //����û��Ƿ����
        user = isUserExist(input);
        if (!user) {
            printf("�û������ڣ����������룡\n");
            system("read");
        } else { break; }
    }
    //�����˺�
    while (true) {
        system("cls");
        UserInformation(user, 0);
        //��ز���
        printf("\n����\n");
        printf("***************************\n");
        printf("*******1����������*********\n");
        printf("*******0���˳�����*********\n");
        printf("***************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�����û�����
        if (select[0] == '1' && strlen(select) == 2) { ResetUserPassword(user); }
            //�˳�����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�鿴��ˮҳ��
void ManagerViewAvailableDrinksMenu() {
    char brand[MaxSize] = {""};
    char taste[MaxSize] = {""};
    char package[MaxSize] = {""};
    char capacity[MaxSize] = {""};
    char activity[MaxSize] = {""};
    Drink *found_drink_head = NULL;    //������ѯ��ˮ����
    while (true) {
        //����
        system("cls");
        if (!found_drink_head) {
            //����Ա�鿴ȫ�����۾�ˮ
            ViewAvailableDrinks(found_drink_head, 0, 0);
            //��ز���
            printf("\n����\n");
            printf("*********************************\n");
            printf("********1���޸ľ�ˮ��Ϣ**********\n");
            printf("********2�������Żݻ**********\n");
            printf("********3��������������ˮ********\n");
            //printf("********4������������************\n");
            printf("********4���¼ܾ�ˮ**************\n");
            printf("********0���˳���ˮ����**********\n");
            printf("*********************************\n");
            printf("����ѡ���ǣ�");
        } else {
            //����Ա�鿴�����������۾�ˮ
            printf("��������\n");
            printf("**************************************\n");
            printf("Ʒ�ƣ�%s\n", brand);
            printf("��ζ��%s\n", taste);
            printf("��װ����(1ƿװ��2��װ��3��װ��4����)��%c\n", package[0]);
            printf("��ƿ������%smL\n", capacity);
            printf("�Żݻ(1�ۿۣ�2��Ʒ��3����)��%c\n", activity[0]);
            printf("**************************************\n");
            ViewAvailableDrinks(found_drink_head, 0, 0);
            //��ز���
            printf("\n����\n");
            printf("*********************************\n");
            printf("********1���޸ľ�ˮ��Ϣ**********\n");
            printf("********2�������Żݻ**********\n");
            printf("********3��������������ˮ********\n");
            printf("********4���¼ܾ�ˮ**************\n");
            //printf("********4������������************\n");
            printf("********0���˳���������**********\n");
            printf("*********************************\n");
            printf("����ѡ���ǣ�");
        }
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�޸ľ�ˮ��Ϣ
        if (select[0] == '1' && strlen(select) == 2) {
            ModifyDrinkInformationMenu(found_drink_head);
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //�����Żݻ
        else if (select[0] == '2' && strlen(select) == 2) {
            SetActivity(found_drink_head, 0);
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //������������ˮ����ҳ��
        else if (select[0] == '3' && strlen(select) == 2) {
            //���ٲ�ѯ��ˮ����
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
            //�����ѯ����
            if (InputDrinkConditions(brand, taste, package, capacity, activity) == 1) {
                //������ѯ��ˮ����
                found_drink_head = CreatFoundDrinkList(brand, taste, package, capacity, activity);
            }
        }
            //�¼ܾ�ˮ
        else if (select[0] == '4' && strlen(select) == 2) {
            TakeDownDrink(found_drink_head, 0);
            if (found_drink_head) {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
        }
            //������һ����
        else if (select[0] == '0' && strlen(select) == 2) {
            //�˳���ˮ����
            if (!found_drink_head) { return; }
                //�˳���ˮ��������
            else {
                DestroyFoundDrinkList(found_drink_head);
                found_drink_head = NULL;
            }
        }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�޸ľ�ˮ��Ϣҳ��
void ModifyDrinkInformationMenu(Drink *found_drink_head) {
    //����Ҫ�޸ĵľ�ˮ
    Drink *drink = NULL;
    while (true) {
        system("cls");
        ViewAvailableDrinks(found_drink_head, 0, 0);
        printf("������Ҫ�޸ľ�ˮ���(����0����)��");
        char drink_ID[MaxSize] = {""};
        fgets(drink_ID, sizeof(drink_ID), stdin);
        //�����Ƿ񷵻�
        if (drink_ID[0] == '0' && strlen(drink_ID) == 2) { return; }
        //�����ˮ�Ƿ����
        drink = isDrinkExist(drink_ID);
        if (!drink->next) {
            printf("δ�ҵ���ˮ�����������룡\n");
            system("read");
        } else { break; }
    }
    //�޸ľ�ˮ��Ϣ
    while (true) {
        system("cls");
        ViewAvailableDrinks(drink, 0, 1);
        printf("\n����\n");
        printf("*********************************\n");
        printf("*********1���޸����ۼ۸�*********\n");
        printf("*********2�������Żݻ*********\n");
        printf("*********3���¼�*****************\n");
        printf("*********0���˳��޸Ľ���*********\n");
        printf("*********************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�޸����ۼ۸�
        if (select[0] == '1' && strlen(select) == 2) { ModifyDrinkSalePrice(drink); }
            //�����Żݻ
        else if (select[0] == '2' && strlen(select) == 2) { SetActivity(drink, 1); }
            //�¼ܾ�ˮ
        else if (select[0] == '3' && strlen(select) == 2) {
            TakeDownDrink(drink, 1);
            return;
        }
            //�˳�����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//����Ա�鿴������Ϣҳ��
void ManagerViewNewMessageMenu() {
    while (true) {
        system("cls");
        printf("*******************************\n");
        printf("**********1���µ���Ϣ**********\n");
        printf("**********2���˻���Ϣ**********\n");
        printf("**********0���˳�����**********\n");
        printf("*******************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�µ���Ϣ
        if (select[0] == '1' && strlen(select) == 2) { ManagerViewOrderInformationMenu(); }
            //�˻���Ϣ
        else if (select[0] == '2' && strlen(select) == 2) { ManagerViewReturnInformationMenu(); }
            //�˳�����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�鿴�µ���Ϣҳ��
void ManagerViewOrderInformationMenu() {
    while (true) {
        system("cls");
        ViewWholesaleRecords(NULL, NULL, 1, 0);
        printf("\n����\n");
        printf("*******************************\n");
        printf("**********1�������µ�**********\n");
        printf("**********0���˳�����**********\n");
        printf("*******************************\n");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�����µ�
        if (select[0] == '1' && strlen(select) == 2) { AcceptOrder(); }
            //�˳�����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//�鿴�˵���Ϣҳ��
void ManagerViewReturnInformationMenu() {
    while (true) {
        system("cls");
        ViewWholesaleRecords(NULL, NULL, 4, 0);
        printf("\n����\n");
        printf("*******************************\n");
        printf("**********1�������˻�**********\n");
        printf("**********0���˳�����**********\n");
        printf("*******************************\n");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�����˻�
        if (select[0] == '1' && strlen(select) == 2) { AcceptReturn(); }
            //�˳�����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}

//����Ա������¼ҳ��
void ManagerViewWholesaleRecordMenu() {
    while (true) {
        char user[MaxSize] = {""};
        char date[MaxSize] = {""};
        char situation[MaxSize] = {""};
        char brand[MaxSize] = {""};
        char taste[MaxSize] = {""};
        char package[MaxSize] = {""};
        char capacity[MaxSize] = {""};
        WholesaleRecord *found_wholesaleRecord_head = NULL;    //������ѯ������¼����
        while (true) {
            system("cls");
            if (!found_wholesaleRecord_head) {
                //����Ա�鿴���е�������¼
                ViewWholesaleRecords(found_wholesaleRecord_head, NULL, 6, 0);
                //��ز���
                printf("\n����\n");
                printf("*********************************\n");
                printf("**********1�����Ҷ���************\n");
                printf("**********2���޸Ķ���************\n");
                printf("**********0���˳�ҳ��************\n");
                printf("*********************************\n");
                printf("����ѡ���ǣ�");
            } else {
                //����Ա�鿴��������������¼
                printf("��������\n");
                printf("**************************************\n");
                printf("�û��˺Ż���ϵ��ʽ��%s\n", user);
                printf("�������ڣ�%s\n", date);
                printf("�����ֿ�(1���µ���2�����У�3�ѵ�����4�����˻���5���˻���6����)��%c\n", situation[0]);
                printf("Ʒ�ƣ�%s\n", brand);
                printf("��ζ��%s\n", taste);
                printf("��װ����(1ƿװ��2��װ��3��װ��4����)��%c\n", package[0]);
                printf("��ƿ������%sml\n", capacity);
                printf("**************************************\n");
                ViewWholesaleRecords(found_wholesaleRecord_head, NULL, 6, 0);
                //��ز���
                printf("\n����\n");
                printf("*********************************\n");
                printf("**********1�����Ҷ���************\n");
                printf("**********2���޸Ķ���************\n");
                printf("**********0���˳�����ҳ��********\n");
                printf("*********************************\n");
                printf("����ѡ���ǣ�");
            }
            //����ѡ��
            char select[MaxSize] = {""};
            fgets(select, sizeof(select), stdin);
            //���Ҷ���
            if (select[0] == '1' && strlen(select) == 2) {
                //���ٲ�ѯ������¼����
                if (found_wholesaleRecord_head) {
                    DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                    found_wholesaleRecord_head = NULL;
                }
                //�����ѯ����
                if (ManagerInputWholesaleRecordConditions(user, date, situation, brand, taste, package, capacity) ==
                    1) {
                    //������ѯ������¼����
                    found_wholesaleRecord_head = CreatManagerFoundWholesaleRecordList(user, date, situation, brand,
                                                                                      taste, package, capacity);
                }
            }
                //�޸Ķ���
            else if (select[0] == '2' && strlen(select) == 2) {
                ManagerModifyAnWholesaleOrder(found_wholesaleRecord_head);
            }
                //������һ����
            else if (select[0] == '0' && strlen(select) == 2) {
                if (!found_wholesaleRecord_head) { return; }
                else {
                    DestroyTempWholesaleRecordList(found_wholesaleRecord_head);
                    found_wholesaleRecord_head = NULL;
                }
            }
                //�Ƿ�����
            else {
                printf("�Ƿ�ѡ�����������룡\n");
                system("read");
            }
        }
    }
}

//����Ա������¼ҳ��
void ManagerViewPurchaseRecordMenu() {
    while (true) {
        char date[MaxSize] = {""};
        char brand[MaxSize] = {""};
        char taste[MaxSize] = {""};
        char package[MaxSize] = {""};
        char capacity[MaxSize] = {""};
        PurchaseRecord *found_purchaseRecord_head = NULL;//������ѯ������¼����
        while (true) {
            system("cls");
            if (!found_purchaseRecord_head) {
                //����Ա�鿴���еĽ�����¼
                ViewPurchaseRecords(found_purchaseRecord_head, 0);
                //��ز���
                printf("\n����\n");
                printf("*********************************\n");
                printf("**********1�����Ҷ���************\n");
                printf("**********2����Ӷ���************\n");
                printf("**********3���޸Ķ���************\n");
                printf("**********0���˳�ҳ��************\n");
                printf("*********************************\n");
                printf("����ѡ���ǣ�");
            } else {
                //����Ա�鿴�������Ľ�����¼
                printf("��������\n");
                printf("**************************************\n");
                printf("�������ڣ�%s\n", date);
                printf("Ʒ�ƣ�%s\n", brand);
                printf("��ζ��%s\n", taste);
                printf("��װ����(1ƿװ��2��װ��3��װ��4����)��%c\n", package[0]);
                printf("��ƿ������%sml\n", capacity);
                printf("**************************************\n");
                ViewPurchaseRecords(found_purchaseRecord_head, 0);
                //��ز���
                printf("\n����\n");
                printf("*********************************\n");
                printf("**********1�����Ҷ���************\n");
                printf("**********2����Ӷ���************\n");
                printf("**********3���޸Ķ���************\n");
                printf("**********0���˳�����ҳ��********\n");
                printf("*********************************\n");
                printf("����ѡ���ǣ�");
            }
            //����ѡ��
            char select[MaxSize] = {""};
            fgets(select, sizeof(select), stdin);
            //���Ҷ���
            if (select[0] == '1' && strlen(select) == 2) {
                //���ٲ�ѯ������¼����
                if (found_purchaseRecord_head) {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = NULL;
                }
                //�����ѯ����
                if (ManagerInputPurchaseRecordConditions(date, brand, taste, package, capacity) == 1) {
                    //������ѯ������¼����
                    found_purchaseRecord_head = CreatManagerFoundPurchaseRecordList(date, brand, taste, package,
                                                                                    capacity);
                }
            }
                //��Ӷ���
            else if (select[0] == '2' && strlen(select) == 2) {
                AddAnPurchaseRecordOrder();
                if (found_purchaseRecord_head) {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = CreatManagerFoundPurchaseRecordList(date, brand, taste, package,
                                                                                    capacity);
                }
            }
                //�޸Ķ���
            else if (select[0] == '3' && strlen(select) == 2) {
                ManagerModifyPurchaseRecordMenu(found_purchaseRecord_head);
                if (found_purchaseRecord_head) {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = CreatManagerFoundPurchaseRecordList(date, brand, taste, package,
                                                                                    capacity);
                }
            }
                //������һ����
            else if (select[0] == '0' && strlen(select) == 2) {
                if (!found_purchaseRecord_head) { return; }
                else {
                    DestroyTempPurchaseRecordList(found_purchaseRecord_head);
                    found_purchaseRecord_head = NULL;
                }
            }
                //�Ƿ�����
            else {
                printf("�Ƿ�ѡ�����������룡\n");
                system("read");
            }
        }
    }
}

//����Ա������¼�޸�ҳ��
void ManagerModifyPurchaseRecordMenu(PurchaseRecord *head) {
    //��ѯ����
    PurchaseRecord *purchase_record = purchaseRecord_head;
    while (true) {
        system("cls");
        ViewPurchaseRecords(head, 0);
        printf("�����붩����(����0����)��");
        char order_number[MaxSize] = {""};
        fgets(order_number, sizeof(order_number), stdin);
        //����Ƿ񷵻�
        if (order_number[0] == '0' && strlen(order_number) == 2) { return; }
        //���Ҷ���
        while (purchase_record->next) {
            if (isInputCorrect(purchase_record->next->order_number, order_number)) { break; }
            purchase_record = purchase_record->next;
        }
        if (!purchase_record->next) {
            printf("���������ڣ����������룡\n");
            system("read");
        } else { break; }
    }
    //�޸���Ϣ
    while (true) {
        system("cls");
        ViewPurchaseRecords(purchase_record, 1);
        //��ز���
        printf("\n����\n");
        printf("*******************************\n");
        printf("*********1���޸�����***********\n");
        printf("*********2���޸�Ʒ��***********\n");
        printf("*********3���޸Ŀ�ζ***********\n");
        printf("*********4���޸İ�װ***********\n");
        printf("*********5���޸ĵ�ƿ����*******\n");
        printf("*********6���޸ĵ�������*******\n");
        printf("*********7���޸Ľ����۸�*******\n");
        printf("*********8���޸Ľ�������*******\n");
        printf("*********0���˳�����***********\n");
        printf("*******************************\n");
        printf("����ѡ���ǣ�");
        //����ѡ��
        char select[MaxSize] = {""};
        fgets(select, sizeof(select), stdin);
        //�޸�����
        if (select[0] == '1' && strlen(select) == 2) { ModifyPurchaseRecordDate(purchase_record); }
            //�޸�Ʒ��
        else if (select[0] == '2' && strlen(select) == 2) { ModifyPurchaseRecordBrand(purchase_record); }
            //�޸Ŀ�ζ
        else if (select[0] == '3' && strlen(select) == 2) { ModifyPurchaseRecordTaste(purchase_record); }
            //�޸İ�װ
        else if (select[0] == '4' && strlen(select) == 2) { ModifyPurchaseRecordPackage(purchase_record); }
            //�޸ĵ�ƿ����
        else if (select[0] == '5' && strlen(select) == 2) { ModifyPurchaseRecordBottleCapacity(purchase_record); }
            //�޸ĵ�������
        else if (select[0] == '6' && strlen(select) == 2) { ModifyPurchaseRecordBoxQuantity(purchase_record); }
            //�޸Ľ����۸�
        else if (select[0] == '7' && strlen(select) == 2) { ModifyPurchaseRecordRestockingPrice(purchase_record); }
            //�޸Ľ�������
        else if (select[0] == '8' && strlen(select) == 2) { ModifyPurchaseRecordGoodsQuantity(purchase_record); }
            //������һ����
        else if (select[0] == '0' && strlen(select) == 2) { return; }
            //�Ƿ�����
        else {
            printf("�Ƿ�ѡ�����������룡\n");
            system("read");
        }
    }
}