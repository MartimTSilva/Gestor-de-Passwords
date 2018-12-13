#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#define MAX_UTILIZADORES 20
#define MAX_RECURSOS 100
#define MAX_ACESSOS 200
#define MAX_CARACTERES 50

typedef struct  ///REGISTER
{
    int ID_Utilizador;
    int NIF_register;
    char username_register[20];
    char password_register[20];
} t_register;

int menu_opcao(void);
int login (t_register user_registo[MAX_UTILIZADORES],int contador);
int registar (t_register user_registo[MAX_UTILIZADORES], int contador, int *seq_ID_Utlizador);

typedef struct
{
    int hora;
    int minutos;
    int dia;
    int mes;
    int ano;
} t_data;

typedef struct
{
    char nome[MAX_CARACTERES];
    char login[MAX_CARACTERES];
    char password[MAX_CARACTERES];
    t_data data;
} t_acessos;

typedef struct
{
    int ID_Recurso;
    int identificador;
    char nome[MAX_CARACTERES];
    char tipo_recurso[MAX_CARACTERES];
    int grau_seguranca;
    char designacao[MAX_CARACTERES];
} t_recursos;

char menuPrincipal(void);
char MenuGestor(void);
void MenuSobre(void);
char MenuGerador(void);
void VerificadorPassword(t_recursos array_recursos[], int contador, char *password[]);
char MenuGestorRecursos(void);
char ConfirmarSaida(void);
char MenuExtras(void);
void VerRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador, int contador_r);
int InserirRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador);
void VerAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador, int contador_r, t_data array_data[MAX_ACESSOS]);
int InserirAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_RECURSOS], int contador, int contador_r, t_data array_data[MAX_ACESSOS]);
char MenuGestorAcessos(void);
void VerUtilizadores(t_register user_register[MAX_UTILIZADORES],int contador, int ID_Utilizador);
int InserirAdmin(t_register user_registo[MAX_UTILIZADORES], int contador);

///Declarações para o menu gerador
void gerador_num(void);
void gerador_letras(int quant4);
void gerador_razovel(int quant);
void gerador_dificil(int quant2);
int menu_opcoes (void);
int le_num(void);
int gerador_nume[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
char gerador_ltr[52] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char gerador_espec[18] = { '_', '.', '-', '$', '/', '&', '(', ')', '[', ']', '?', '!', '@', '=', '+', '*' };


int main()
{
    system("chcp 65001"); //Para usar caracteres especiais.
    system("cls"); //Limpa o ecrã
    char opcao, opcao2, opcao3, opcao4, opcao5, opcao6, sair;
    t_data array_data[MAX_ACESSOS];
    t_acessos arr_acessos[MAX_ACESSOS] = {"", "", ""};
    t_recursos arr_recursos[MAX_RECURSOS] = {"", "", "", "", ""};
    int contador_array_recursos = 0, pwd, contador_recursos = 0,confirmarLogin, contador_registar=0, seq_ID_Utlizador=0, seq_ID_Recursos;

    int opc_register;
    t_register user_register[MAX_UTILIZADORES];
    contador_registar = InserirAdmin(user_register, contador_registar);
    do
    {
        do
        {
            opc_register=menu_opcao();
            switch(opc_register)
            {
            case 1:
                confirmarLogin = login(user_register,contador_registar);
                break;
            case 2:
                contador_registar=registar(user_register, contador_registar, &seq_ID_Utlizador);
                break;
            case 3:
                sair = ConfirmarSaida();
                break;
            }
        }
        while(confirmarLogin != 1);
        confirmarLogin=0;
        do
        {
            opcao=menuPrincipal();
            switch (opcao)
            {
            case 'A':
                do
                {
                    opcao2=MenuGestor();
                    switch(opcao2)
                    {
                    case 'A':
                        do
                        {
                            opcao3 = MenuGestorAcessos();
                            switch (opcao3)
                            {
                            case 'A':
                                if (contador_array_recursos < MAX_RECURSOS) ///Para não deixar exceder o número máximo de recursos permitidos
                                {
                                    contador_array_recursos = InserirAcessos(arr_acessos, arr_recursos, contador_array_recursos, contador_recursos, array_data);
                                }
                                else
                                {
                                    printf("\nNúmero máximo de acessos excedido!\n");
                                    getch();
                                }
                                break;
                            case 'B':
                                VerAcessos(arr_acessos, arr_recursos, contador_array_recursos, contador_recursos, array_data);
                                break;
                            case 'V':
                                break;
                            default:
                                printf("\n\tOpção Inválida!\n");
                                getch();
                            }
                        }
                        while (opcao3 != 'V');
                        break;
                    case 'B':
                        do
                        {
                            opcao4 = MenuGestorRecursos();
                            switch(opcao4)
                            {
                            case 'A':
                                if (contador_recursos < MAX_RECURSOS) ///Para não deixar exceder o número máximo de recursos permitidos
                                {
                                    contador_recursos = InserirRecursos(arr_recursos, contador_recursos);
                                }
                                else
                                {
                                    printf("\nNúmero máximo de recursos excedido!\n");
                                    getch();
                                }
                                break;
                            case 'B':
                                VerRecursos(arr_recursos, contador_recursos, contador_recursos);
                                break;
                            case 'C':
                                printf("\nA funcionalidade alterar recursos está incompleta");
                                break;
                            case 'D':
                                printf("\nA funcionalidade eliminar recursos está incompleta");
                                break;
                            case 'V':
                                break;
                            default:
                                printf("\n\tOpção Inválida!\n");
                                getch();
                            }
                        }
                        while (opcao4 != 'V');
                        break;

                    case 'C':
                        VerUtilizadores(user_register, contador_registar, &seq_ID_Utlizador);
                        getch();
                        break;
                    case 'D':
                        printf("\nA funcionalidade das estatisticas ainda não está feito\n");
                        getch();
                        break;
                    case 'V':
                        break;
                    default:
                        printf("\n\tOpção Inválida!\n");
                        getch();
                    }
                }
                while(opcao2 != 'V');
                break;
            case 'B':
                do
                {
                    opcao5 = MenuExtras();
                    switch(opcao5)
                    {
                    case 'A':
                        do
                        {
                            opcao6=MenuGerador();
                            switch(opcao6)
                            {
                            case 'A':
                                gerador_num();
                                break;
                            case 'B':
                                pwd=le_num();
                                gerador_letras(pwd);
                                break;
                            case 'C':
                                pwd=le_num();
                                gerador_razovel(pwd);
                                break;
                            case 'D':
                                pwd=le_num();
                                gerador_dificil(pwd);
                                break;
                            case 'V':
                                break;
                            default:
                                printf("\n\tOpção Inválida!\n");
                                getch();
                            }
                        }
                        while(opcao6 != 'V');
                        break;
                    case 'B':
                        MenuSobre();
                        break;
                    case 'V':
                        break;
                    default:
                        printf("\n\tOpção Inválida!\n");
                        getch();
                    }
                }
                while(opcao5 != 'V');
                break;

            case 'C':
                break;
            case 'S':
                sair = ConfirmarSaida();
                return 0;
                break;
            default:
                printf("\n\tOpção Inválida!\n");
            }
        }
        while (opcao != 'C');
    }
    while(sair == 'S');

    return 0;
}
char menuPrincipal(void)
{
    char opcao;
    system("cls");

    printf("\n");
    printf("\t                ________________              \n");
    printf("\t               | MENU PRINCIPAL |             \n");
    printf("\t ______________|________________|_____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gestor de Passwords                    /\n");
    printf("\t/  B - EXTRAS                                 \\\n");
    printf("\t\\  C - Trocar de conta                        /\n");
    printf("\t/  S - Sair                                   \\\n");
    printf("\t\\_____________________________________________/\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao);
    opcao = toupper(opcao);

    return opcao;
}

char MenuGestor(void)
{
    char opcao2;
    system("cls");

    printf("\n");
    printf("\t                _________________             \n");
    printf("\t               |   MENU GESTOR   |            \n");
    printf("\t ______________|_________________|____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gerir Acessos                          /\n");
    printf("\t/  B - Gerir Recursos                         \\\n");
    printf("\t\\  C - Gerir Utilizadores                     /\n");
    printf("\t/  D - Estatisticas (Incompleto)              \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao2);
    opcao2 = toupper(opcao2);

    return opcao2;
}

char MenuGestorAcessos(void)
{
    char opcao3;
    system("cls");

    printf("\n");
    printf("\t                __________________              \n");
    printf("\t               |  GESTOR ACESSOS  |             \n");
    printf("\t ______________|__________________|_____________\n");
    printf("\t/                                              \\\n");
    printf("\t\\  A - Inserir Acessos                         /\n");
    printf("\t/  B - Consultar Acessos                       \\\n");
    printf("\t\\  C - Alterar Acessos (Incompleto)            /\n");
    printf("\t/  D - Eliminar Acessos (Incompleto)           \\\n");
    printf("\t\\  V - Voltar                                  /\n");
    printf("\t/______________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao3);
    opcao3 = toupper(opcao3);

    return opcao3;
}

char MenuGestorRecursos(void)
{
    char opcao4;
    system("cls");

    printf("\n");
    printf("\t                ___________________              \n");
    printf("\t               |  GESTOR RECURSOS  |             \n");
    printf("\t ______________|___________________|_____________\n");
    printf("\t/                                                \\\n");
    printf("\t\\  A - Inserir Recursos                          /\n");
    printf("\t/  B - Consultar Recursos                        \\\n");
    printf("\t\\  C - Alterar Recursos (Incompleto)             /\n");
    printf("\t/  D - Eliminar Recursos (Incompleto)            \\\n");
    printf("\t\\  V - Voltar                                    /\n");
    printf("\t/________________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao4);
    opcao4 = toupper(opcao4);

    return opcao4;
}

char MenuExtras(void)
{
    char opcao5;
    system("cls");

    printf("\n");
    printf("\t                _________________             \n");
    printf("\t               |   MENU EXTRAS   |            \n");
    printf("\t ______________|_________________|____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gerador de Passwords                   /\n");
    printf("\t/  B - Sobre                                  \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao5);
    opcao5 = toupper(opcao5);

    return opcao5;
}


void MenuSobre(void)
{
    system("cls");
    printf("\t                 _________________             \n");
    printf("\t                |      SOBRE      |            \n");
    printf("\t _______________|_________________|____________\n");
    printf("\t/                                              \\\n");
    printf("\t\\     Projeto de Fundamento de Porgramação     /\n");
    printf("\t/                 Elaborado por:               \\\n");
    printf("\t\\            Martim Silva nº2180686            /\n");
    printf("\t/          Gabriel Marques nº2180637           \\\n");
    printf("\t\\                                              /\n");
    printf("\t/                            TeSP PSI - PL4    \\\n");
    printf("\t\\______________________________________________/\n");
    printf("\t Pressione qualquer tecla para voltar\n");
    getch();
}


char MenuGerador(void)
{
    char opcao6;
    system("cls");

    printf("\n");
    printf("\t                ________________              \n");
    printf("\t               |  MENU GERADOR  |             \n");
    printf("\t ______________|________________|_____________\n");
    printf("\t/                                             \\\n");
    printf("\t\\  A - Gerar password só com números          /\n");
    printf("\t/  B - Gerar password só com letras           \\\n");
    printf("\t\\  C - Gerar password com numeros e letras    /\n");
    printf("\t/  D - Gerar password com todos os caracteres \\\n");
    printf("\t\\  V - Voltar                                 /\n");
    printf("\t/_____________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    fflush(stdin);
    scanf(" %c", &opcao6);
    opcao6 = toupper(opcao6);

    return opcao6;
}


char ConfirmarSaida(void)
{
    char sair;

    printf("______________________________________________________________________\n");
    printf("\tQuer mesmo sair? [S/N]: ");
    fflush(stdin);
    sair = getchar();
    return sair;
}


int InserirRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador)
{
    char nome_recurso[MAX_CARACTERES];
    int encontrado, i;

    printf("______________________________________________________________________\n");
    printf("\nIndique o nome do novo recurso: ");
    scanf(" %s", nome_recurso);

    for(i = 0; i < contador; i++)
    {

        encontrado = strcasecmp(array_recursos[i].nome, nome_recurso);
        if (encontrado == 0)
        {
            printf("Já tem um recurso criado com esse nome.");
            getch();
            return contador;
        }
    }

    if (i == contador && encontrado != 0)
    {
        strcpy(array_recursos[contador].nome, nome_recurso);
        printf("\nInsira os dados\n");
        printf("Tipo de recurso:");
        fflush(stdin);
        gets(array_recursos[i].tipo_recurso);
        printf("Designação única: ");
        fflush(stdin);
        gets(array_recursos[i].designacao);
        do
        {
            printf("Grau de segurança (1 - Baixo | 2 - Médio | 3 - Elevado): ");
            fflush(stdin);
            scanf("%d", &array_recursos[i].grau_seguranca);
        }
        while (array_recursos[i].grau_seguranca <1 || array_recursos[i].grau_seguranca > 3);
        printf("\nRecurso criado com sucesso!");
        contador+=1;
    }
    printf("\n______________________________________________________________________\n\n");

    getch();
    return contador;
}


void VerRecursos(t_recursos array_recursos[MAX_RECURSOS], int contador, int contador_r)
{
    char mostrar[MAX_CARACTERES];
    int i = 0, contador_recursos=0,comparar_recursos;

    if (contador != 0)
    {
        printf("______________________________________________________________________\n\n");
        printf("Todos os os recursos guardados:\n\n");

        for(int i = 0; i < contador; i++ )  ///Ver a lista de contas
        {
            printf("%i - %s\n", i+1, array_recursos[i].nome); ///i+1 para a lista dos recursos não começar em 0
        }
        printf("\n______________________________________________________________________\n\n");
    }
    else
    {
        printf("\nNão tem recursos guardados.\n");
    }

    printf("Indique o nome do recurso que pretende consultar: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for (i = 0; i < contador_r; i++)
    {
        comparar_recursos = strcasecmp(array_recursos[i].nome, mostrar);
        if (comparar_recursos == 0)
        {
            printf("Tipo de recurso: %s\n", array_recursos[i].tipo_recurso);
            printf("Designação única: %s\n", array_recursos[i].designacao);
            printf("Grau de segurança: %i\n", array_recursos[i].grau_seguranca);
            printf("ID: %i\n", array_recursos[i].ID_Recurso);
            contador_recursos++;
        }
    }

    if (contador_recursos == 0 && comparar_recursos != 0)
    {
        printf("O recurso que introduziu não existe.\n");
        printf("______________________________________________________________________\n\n");
        getch();
        return;
    }

    printf("______________________________________________________________________\n\n");
    getch();
}


void VerAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_ACESSOS], int contador, int contador_r, t_data array_data[MAX_ACESSOS])
{
    char mostrar[MAX_CARACTERES];
    int i = 0, encontrado=99, contador_acessos=0, contador_recursos=0,comparar_recursos;

    printf("______________________________________________________________________\n\n");
    printf("Indique o nome do recurso que pretende consultar: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for (i = 0; i < contador_r; i++)
    {
        comparar_recursos = strcasecmp(array_recursos[i].nome, mostrar);
        if (comparar_recursos == 0)
        {
            contador_recursos++;
        }
    }

    if (contador_recursos == 0 && comparar_recursos != 0)
    {
        printf("O recurso que introduziu não existe.\n");
        printf("______________________________________________________________________\n\n");
        getch();
        return;
    }

    for(i = 0; i < contador; i++)
    {
        encontrado = strcasecmp(array_acessos[i].nome, mostrar);
        if (encontrado == 0)
        {
            printf("-----------------");
            printf("\nLogin: %s\nPassword: %s\n", array_acessos[i].login, array_acessos[i].password);
            printf("\nHora: %i:%i\n", array_acessos[i].data.hora, array_acessos[i].data.minutos);
            printf("Data: %i/%i/%i\n", array_acessos[i].data.dia, array_acessos[i].data.mes, array_acessos[i].data.ano);
            printf("-----------------\n");
            contador_acessos++; ///Contador necessário para verificar se não existe nenhum acesso com esse recurso.
        }
    }

    if(contador_acessos == 0 && encontrado != 0)
        printf("O recurso que introduziu não tem acessos.\n");
    printf("______________________________________________________________________\n\n");
    getch();
}

int InserirAcessos(t_acessos array_acessos[MAX_ACESSOS], t_recursos array_recursos[MAX_ACESSOS], int contador, int contador_r, t_data array_data[MAX_ACESSOS])
{
    char mostrar[MAX_CARACTERES], password[MAX_CARACTERES];
    int encontrado=1;

    printf("______________________________________________________________________\n\n");
    printf("Indique o nome do recurso em que pretende guardar os acessos: ");
    fflush(stdin);
    gets(mostrar);
    printf("\n");

    for(int i = 0; i < contador_r; i++)
    {
        encontrado = strcasecmp(array_recursos[i].nome, mostrar);
        if (encontrado == 0)
        {
            strcpy(array_acessos[contador].nome, mostrar);
            printf("\nInsira os seus dados\n\n");
            printf("Login: ");
            scanf(" %s", array_acessos[contador].login);

            VerificadorPassword(array_recursos, i, &password);
            strcpy(array_acessos[contador].password, password);

            printf("\nIntroduza a data e hora\n");

            do
            {
                printf("Hora: ");
                fflush(stdin);
                scanf("%i", &array_acessos[contador].data.hora);
                if (array_acessos[contador].data.hora > 24)
                    printf("Hora inválida.\n");
            }
            while (array_acessos[contador].data.hora > 23);

            do
            {
                printf("Minutos: ");
                fflush(stdin);
                scanf("%i", &array_acessos[contador].data.minutos);
                if (array_acessos[contador].data.minutos > 59)
                    printf("Minutos inválidos.\n");
            }
            while (array_acessos[contador].data.minutos > 59);

            do
            {
                printf("Dia: ");
                fflush(stdin);
                scanf("%i", &array_acessos[contador].data.dia);
                if (array_acessos[contador].data.dia > 31)
                    printf("Dia inválido.\n");
            }
            while (array_acessos[contador].data.dia > 31);

            do
            {
                printf("Mês: ");
                fflush(stdin);
                scanf("%i", &array_acessos[contador].data.mes);
                if (array_acessos[contador].data.mes > 12)
                    printf("Mês inválido.\n");
            }
            while (array_acessos[contador].data.mes > 12);

            do
            {
                printf("Ano: ");
                fflush(stdin);
                scanf("%i", &array_acessos[contador].data.ano);
                if (array_acessos[contador].data.ano > 2019 || array_acessos[contador].data.ano < 1920)
                    printf("Ano inválido.\n");
            }
            while (array_acessos[contador].data.ano > 2019 || array_acessos[contador].data.ano < 1920);

            contador += 1;
            printf("\nAcesso adicionado com sucesso!");
            break;
        }
    }

    if (encontrado != 0)
    {
        printf("Recurso não encontrado. Crie um recurso antes de guardar os acessos.");
    }
    printf("\n______________________________________________________________________\n\n");
    getch();
    return contador;
}

void VerificadorPassword(t_recursos array_recursos[], int contador, char *password[])
{
    int espec=0,maiusc=0,minusc=0, num=0,i=0, tamanho, total;
    char verificar_password[25];

    if (array_recursos[contador].grau_seguranca == 3)
    {
        printf("\nEscolheu o grau de segurança máximo para este recurso, por isso a sua password tem que ter:\n");
        printf("Pelo menos 8 caracteres, um número, um caracter especial, uma letra maiúscula e minúscula.\n\n");
        do
        {
            espec=0, maiusc=0, minusc=0, num=0;
            printf("\nPassword: ");
            scanf(" %s", verificar_password);
            tamanho=strlen(verificar_password);
            for(i=0; i<tamanho; i++)
            {
                if(ispunct(verificar_password[i]))
                {
                    espec++;

                }
                if(isupper(verificar_password[i]))
                {
                    maiusc++;
                }
                if(islower(verificar_password[i]))
                {
                    minusc++;
                }
                if(isdigit(verificar_password[i]))
                {
                    num++;
                }
            }

            if (espec == 0)
            {
                printf("Falta um caracter especial\n");
            }
            if (maiusc == 0)
            {
                printf("Falta uma letra maiúscula\n");
            }
            if (minusc == 0)
            {
                printf("Falta uma letra minúscula\n");
            }
            if (num == 0 )
            {
                printf("Falta um número\n");
            }
            if(tamanho<8)
                printf("Password demasiado pequena\n");
        }
        while (espec == 0 || maiusc == 0 || minusc == 0 || num == 0 || tamanho < 8);
        strcpy(password, verificar_password);
    }

/////////////////////////////////////////////////////////////////////////////////////////


    if (array_recursos[contador].grau_seguranca == 2)
    {
        printf("\nEscolheu o grau de segurança médio para este recurso, por isso a sua password tem que ter:\n");
        printf("Pelo menos 8 caracteres, um número, uma letra maiúscula e minúscula.\n\n");
        do
        {
            espec=0, maiusc=0, minusc=0, num=0;
            printf("\nPassword: ");
            scanf("%s", verificar_password);
            tamanho=strlen(verificar_password);
            for(i=0; i<tamanho; i++)
            {
                if(isupper(verificar_password[i]))
                    maiusc++;
                if(islower(verificar_password[i]))
                    minusc++;
                if(isdigit(verificar_password[i]))
                    num++;
            }
            if (maiusc == 0)
                printf("Falta uma letra maiúscula\n");
            if (minusc == 0)
                printf("Falta uma letra minúscula\n");
            if (num == 0)
                printf("Falta um número\n");
            if(tamanho<8)
                printf("Password demasiado pequena\n");

        }
        while (maiusc == 0 || minusc == 0 || num == 0 || tamanho < 8);
        strcpy(password, verificar_password);
    }

///////////////////////////////////////////////////////////////////////////////////

    if (array_recursos[contador].grau_seguranca == 1)
    {
        printf("\nEscolheu o grau de segurança baixo para este recurso, por isso pode ser o que quiser:\n");
        printf("\nPassword: ");
        scanf("%s", verificar_password);
        strcpy(password, verificar_password);
    }
}



///Funções do Gerador de Passwords

int le_num(void)
{
    int num;
    printf("\n______________________________________________________________________\n\n");
    printf("Introduza a quantidade de caracteres que deseja [8-16]: ");
    fflush(stdin);
    scanf("%d", &num);
    return num;
}


void gerador_num(void)
{
    int numeros, n;

    printf("\n______________________________________________________________________\n\n");
    printf("Introduza a quantidade de número que deseja [4-16]: ");
    fflush(stdin);
    scanf("%d", &numeros);
    if (numeros > 3 && numeros < 17)
    {
        printf("\nA password gerada foi: ");
        srand(time(0));

        for(n = 1; n <= numeros; n++)
        {
            printf("%d", gerador_nume[rand()%11]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    printf("\n\n");
    getch();
}


void gerador_letras(int quant4)
{
    int n;

    if (quant4 > 7 && quant4 < 17)
    {
        srand(time(0));
        printf("\nA password gerada foi: ");
        for(n = 1; n <= quant4; n++)

        {
            printf("%c", gerador_ltr[rand()%57]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    printf("\n\n");
    getch();
}


void gerador_razovel(int quant)
{
    int qtn;
    int n;

    if (quant > 7 && quant < 17)
    {
        qtn = quant / 2;
        printf("\nA password gerada foi: ");
        srand(time(0));

        for(n = 1; n <= qtn; n++)
        {
            printf("%c", gerador_ltr[rand()%57]);
            printf("%d", gerador_nume[rand()%11]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    printf("\n\n");
    getch();
}


void gerador_dificil(int quant2)
{
    int qtn;
    int n=0;

    if (quant2 > 7 && quant2 < 17)
    {
        qtn = quant2 / 2;

        printf("\nA password gerada foi: ");
        srand(time(0));

        for(n = 1; n <=qtn; n++)
        {
            printf("%c", gerador_ltr[rand()%57]);

            if(n % 2 == 0)
            {
                if((rand()%11) % 2 == 0)
                    printf("%c", gerador_espec[rand()%21]);

                else
                    printf("%d", gerador_nume[rand()%11]);
            }

            else
                printf("%d", gerador_nume[rand()%11]);
        }
    }
    else
    {
        printf("ERRO\n");
    }
    getch();
}
int menu_opcao(void)
{
    int opcao;
    system("cls");
    printf("\n");
    printf("\t                _________________________             \n");
    printf("\t               |   GESTOR DE PASSWORDS   |            \n");
    printf("\t ______________|_________________________|____________\n");
    printf("\t/                                                    \\\n");
    printf("\t\\  1 - Login                                         /\n");
    printf("\t/  2 - Registar                                      \\\n");
    printf("\t\\  3 - Sair                                          /\n");
    printf("\t/____________________________________________________\\\n");
    printf("\n");
    printf("\tOpção --> ");
    scanf("%i", &opcao);    return opcao;
}

int login(t_register user_registo[MAX_UTILIZADORES],int contador)
{
    char NIF_login[10];
    char username_login[MAX_CARACTERES];
    char password_login[MAX_CARACTERES];
    int confirmar=0, i;

    system("cls");

    printf("\n\t|========================| LOGIN |========================|\n\n");
    printf("\t  Username: ");
    fflush(stdin);
    scanf("%s",username_login);
    printf("\n\t  Password: ");
    fflush(stdin);
    scanf("%s",password_login);

    for(i = 0; i < contador ; i++)
    {
        if((strcmp(user_registo[i].username_register,username_login)==0) && (strcmp(user_registo[i].password_register,password_login)==0))
        {
            confirmar=1;
            break;
        }
    }

    if(strcmp(user_registo[i].password_register,password_login)!=0)
    {
        printf("\n\t  Credenciais erradas!\n\n");
        getch();
    }

    return confirmar;
}


int registar(t_register user_registo[MAX_UTILIZADORES], int contador, int *seq_ID_Utlizador)
{
    int i, tam, encontrado=0, nif, existe = 0;
    char utilizador[MAX_CARACTERES];
    system("cls");
    printf("\n\t|========================| REGISTAR |========================|\n");
    do
    {
        do
        {
            printf("\n\t  Username: ");
            fflush(stdin);
            gets(utilizador);

            for(i = 0; i < contador ; i++)

            {
                if (strcmp(user_registo[i].username_register, utilizador)==0)
                {
                    printf("\n\t  Esse nome de utilizador já existe.\n");
                    getch();
                    break;
                }

            }
        }
        while (utilizador != "admin" && strcmp(user_registo[i].username_register, utilizador)==0);


        do
        {
            printf("\n\t  Numero de identificação fiscal (NIF): ");

            fflush(stdin);
            scanf("%i", &nif);
            if(nif < 111111111 || nif > 999999999)
            {
                printf("\n\t  O NIF necissita de ter 9 numeros. \n");
            }
            for(i=0; i< contador; i++)
            {
                if (user_registo[i].NIF_register==nif)
                {
                    existe = 1;
                    printf("\n\t  Esse NIF já existe.");
                }
                else{
                    existe = 0;
                }
            }
        }
        while(nif > 111111111 && nif < 999999999 && existe==1);

    }
    while(strcmp(user_registo[i].username_register, utilizador)==0 && user_registo[contador].NIF_register==nif);

    printf("\n\t  Password: ");
    scanf("%s", user_registo[contador].password_register);
    strcpy(user_registo[contador].username_register, utilizador);
    user_registo[contador].NIF_register = nif;
    printf("\n\t  Registo efetuado com sucesso.\n\n");
    printf("\t|============================================================|\n");
    (*seq_ID_Utlizador)++;
    user_registo[contador].ID_Utilizador = *seq_ID_Utlizador;
    getch();

    return contador+1;
}
void VerUtilizadores(t_register user_register[MAX_UTILIZADORES],int contador, int ID_Utilizador)
{
    int i;
    for (i = 0; i < contador; i++)
    {
        printf("Nome de Utilizador : %s\n", user_register[i].username_register);
        printf("Numero de identificação fiscal: %i\n", user_register[i].NIF_register);
        printf("Palavra-Pass: %s\n", user_register[i].password_register);
        printf("ID: %i\n", user_register[i].ID_Utilizador);
    }
}
int InserirAdmin(t_register user_register[MAX_UTILIZADORES], int contador)
{
    user_register[contador].ID_Utilizador=0;
    user_register[contador].NIF_register=999999999;
    strcpy(user_register[contador].username_register, "admin");
    strcpy(user_register[contador].password_register, "admin");
    return contador+1;
}
