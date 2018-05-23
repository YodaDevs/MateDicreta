#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int verPrimo=0;
long int primo1, primo2;
long int textocrip[1000];
long int inverso;

//achar o d para chave privada usada na descriptação
long long int querod(long int e){

    int i,d=1;

        for(i=1;(d*e)%inverso!=1; i++)
        {
                d=i;
        }

    return d;

}

// formula: resul = a^b % n
long int expModular(long long int a, long long int b, long long int n){

    long int i,resul=1;

    if(n==1) return 0;

    for(i=0; i < b; i++)
    {
        resul = (resul*a) % n;
    }

    return resul;

}

void descriptografar(){

    long long int d, p, q, contad=0;
    long long int mensagem[100], mensagemC[100];
    int i=0;
    FILE *descript, *porascii;

    printf("Digite o valor de D, P e Q: \n");
    scanf("%lld %lld %lld", &d, &p, &q);

    descript = fopen("descriptar.txt","w");
    fclose(descript);
    porascii = fopen("descriptadoemascii.txt", "w");
    fclose(porascii);

    printf("\nDigite a mensagem cript.(obs: digite -1 para encerrar a entrada):\n");

    for(i=0; ;i++)
    {
        scanf("%lld", &mensagemC[i]);
        contad++;
        if(mensagemC[i]==-1) break;
    }

    for(i = 0; i < contad-1; i++)
    {
		mensagem[i] = expModular(mensagemC[i], d, p*q);
	}

	descript = fopen("descriptar.txt","r+");

	for(i = 0; i < contad-1; i++)
    {
		fprintf(descript,"%lld ", mensagem[i]);
	}

	fclose(descript);
	
	porascii = fopen("descriptadoemascii.txt", "r+");

	for(i = 0; i < contad-1; i++)
    	{
        fprintf(porascii, "%c ", mensagem[i]);
	}
	fclose(porascii);
	
}

 void criptografar(){

    int i=0;
    char texto[100];
    long long int n,e,C,aux, auxiliadora, auxtext, acumuladora = 0;
    FILE *cripto;
    cripto = fopen("cripto.txt","w");
    fclose (cripto);


    printf("\nEscreva um texto:\n");
    fgets(texto, 1000, stdin);

    printf("Digite o valor n da chave publica:\n");
    scanf("%lld", &n);

    printf("Digite o valor e da chave publica:\n");
    scanf("%lld", &e);

    for(i = 0; i < strlen(texto); i++)
    {

        aux = texto[i];
		textocrip[i] = expModular(aux, e, n);
        aux=0;
		acumuladora++;

	}

	cripto = fopen("cripto.txt","r+");

    for(i=0; i < acumuladora; i++)
    {

        fprintf(cripto,"%lld ", textocrip[i]);

    }

    printf("\n");
    fclose (cripto);

 }

//euclides para verificação do mdc(e,mult)
long int euclides(long int e, long int mult){

    long int aux;

    if(e%mult==0)
    {
        return mult;
    }
    else
    {
        aux = mult;
        mult = e%mult;
        e = aux;
    }

    euclides(e,mult);

}

long int verificarPrimo(long int primo){

    int i, j;
    long long int cont=0;

    verPrimo = 0;

    for(i=1; i<=sqrt(primo); i++)
    {
        if(primo % i == 0)
        {
            cont++;
        }

    }

    if(cont==1)
    {
         return verPrimo = 1;
    }
    else
    {
        return verPrimo = 0;
    }

}

long int gerarChavePublica(){

        long int coloqueinoarquivo,pri1, pri2, mult = 0, e, euclidizinho=0;
        char opcao;

        FILE *chavepublic, *privateD;

        chavepublic = fopen("chavepublic.txt","w");
        fclose(chavepublic);
        privateD = fopen("privateD.txt","w");
        fclose(privateD);

        printf("\nVoce ira querer numeros primos para P e Q? (S ou N)\n");

        scanf("%c", &opcao);

        if(opcao == 'S')
        {

            printf("\n2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59\n 61 67 71 73 79 83 89 97 101 103 107\n 109 113 127 131 137\n");
            printf("139 149 151 157 163 167 173 179 181 191 193 197\n 199 211 223 227 229 233 239 241 251 257\n 263 269 271 277 281 283 293\n");

        }
            printf("\nDigite dois numeros primos P e Q: \n");
            scanf("%ld %ld", &primo1, &primo2);

            pri1 = verificarPrimo(primo1);
            pri2 = verificarPrimo(primo2);

            if(pri1==0 || pri2==0)
            {
                while(pri1==0)
                {
                    printf("O numero P nao eh primo, por favor, digite outro valor: \n");
                    scanf("%ld", &primo1);

                    pri1 = verificarPrimo(primo1);

                }
                while(pri2==0)
                {
                    printf("O numero Q nao eh primo, por favor, digite outro valor: \n");
                    scanf("%ld", &primo2);

                    pri2 = verificarPrimo(primo2);
                }

            }

            printf("\nNumeros P e Q sao primos!\n");

            printf("P = %ld  Q = %ld\n", primo1, primo2);

            mult = (primo1-1)*(primo2-1);
            inverso = mult;

            printf("Digite um numero E relativamente primo a (p-1)(q-1) = %ld\n", mult);
            scanf("%ld", &e);

            euclidizinho = euclides(e, mult);

            while(euclidizinho!=1)
            {

                printf("\nDigite um outro valor valido para E: \n");
                scanf("%ld", &e);
                euclidizinho = euclides(e, mult);

            }

            printf("\nValor E eh valido\n");

            //PRIVATE KEY
            coloqueinoarquivo = querod(e);

            chavepublic = fopen("chavepublic.txt","r+");
            fprintf(chavepublic,"N = %ld, E = %ld", primo1*primo2, e);
            fclose (chavepublic);
            privateD = fopen("privateD.txt", "r+");
            fprintf(chavepublic, "D = %ld, P = %ld, Q = %ld", coloqueinoarquivo, primo1, primo2);
            fclose(privateD);

}

int main()
{
    int opcao;

    printf("Digite uma das 3 opcoes: \n\n");

    printf("1 - Gerar chave publica\n");
    printf("2 - Criptografar\n");
    printf("3 - Descriptografar\n\n");

    scanf("%d", &opcao);
    getchar();

    if(opcao == 1)
    {
        gerarChavePublica();
    }
    else if(opcao == 2)
    {
        criptografar();
    }
    else if(opcao == 3)
    {
        descriptografar();
    }
    else
    {
        printf("Opcao invalida!\n");
    }

}
