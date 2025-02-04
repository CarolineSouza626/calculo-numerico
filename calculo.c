#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX 10

typedef float (*funcao)(float);

void bisseccao(float a, float b, float erro, funcao f);

void newton_raphson(float a, float erro, funcao f, funcao df);

int gauss_seidel(float m[MAX][MAX], float b[MAX], float x[MAX], int n, float erro);

void bisseccao(float a, float b, float erro, funcao f)
{
    // verifica se existe raiz no intervalo
    if (f(a) * f(b) < 0)
    {
        // zera as variaveis auxiliares
        float c = 0;
        float erroa = 0;
        float errob = 0;
        int i = 0;
        do
        {
            // incrementa a variavel i para evitar loop infinito
            i++;
            // calcula o meio do intervalo
            c = (a + b) / 2;
            // verifica em qual metade esta a raiz
            if (f(a) * f(c) < 0)
            {
                b = c;
            }
            else
            {
                a = c;
            }
            // atualiza a situação
            printf("Na iteração %d a raiz é aproximandamente: %f\n", i, c);
            // calcula o erro em função do intervalo
            erroa = a - c;
            errob = b - c;
            // garante o modulo do erro
            if (erroa < 0)
            {
                erroa = -erroa;
            }
            if (errob < 0)
            {
                errob = -errob;
            }
            // condição de parada
        } while ((erroa > erro || errob > erro));
        printf("A raiz é aproximadamente: %f\n", c);
    }
    else
    {
        printf("Sem raiz nesse intervalo.\n");
    }
}

void newton_raphson(float a, float erro, funcao f, funcao df)
{
    float x = 0;
    float xant;
    int i = 0;
    do
    {
        xant = x;
        x = x - (f(x)) / (df(x));
        i++;
        printf("\nInteracao: %d raiz: %f f(x): %f", i, x, f(x));
    } while (fabs((x - xant) / x) > erro);
    printf("\nA raiz eh aproximadamente: %f\n", x);
}

int gauss_seidel(float a[MAX][MAX], float b[MAX], float x[MAX], int n, float erro)
{
    int i, j, t = 0;
    float y[MAX], maiorErro, vErro[MAX];
    printf("\n");
    // verifica se algum a(i,i) e igual a zero
    for (i = 0; i < n; i++)
    {
        if (a[i, i] == 0)
        {
            printf("O a(%d,%d) é igual a ZERO!!!\n", i + 1, i + 1);
            return 0;
        }
    }
    do
    {
        for (i = 0; i < n; i++)
        {
            // calcula o valor atualizado de x
            y[i] = (b[i] / a[i][i]);
            for (j = 0; j < n; j++)
            {
                if (j != i)
                {
                    y[i] = y[i] - ((a[i][j] / a[i][i]) * x[j]);
                }
            }
            // calcula o erro
            vErro[i] = (y[i] - x[i]) / y[i];
            vErro[i] = abs(vErro[i]);
            // atualiza x
            x[i] = y[i];

            printf("x(%d) = %f   ", i + 1, y[i]);
        }
        // verifica qual o maior erro
        maiorErro = 0;
        for (i = 0; i < n; i++)
        {
            if (vErro[i] > maiorErro)
            {
                maiorErro = vErro[i];
            }
        }
        t++;
        printf("\n");
        // Condição da parada
    } while (maiorErro >= erro);
    printf("Com erro de %f e %d loops, os valores finais de x:\n", maiorErro, t);
    for (i = 0; i < n; i++)
    {
        printf("x(%d) = %f\n", i + 1, x[i]);
    }
    return 1;
}

// definição da função f(x)
float f(float x)
{
    float y;

    float R = x;
    float L = 5;
    float t = 0.05;
    float C = 0.0001;
    float qq0 = 0.01;

    y = exp(-1 * (R * t / (2 * L))) * cos(sqrt(1 / (L * C) - pow(R / (2 * L), 2)) * t) - qq0;

    return y;
}
float g(float x)
{
    return (x - cos(x));
}
float dg(float x)
{
    return (1 + sin(x));
}

int main()
{
    // definindo as variaves
    int opc = 0;
    float ma[MAX][MAX], vb[MAX], vx[MAX], erro, a, b;
    int n, i, j;
    do
    {
        // menu
        printf("\n");
        printf("Escolha uma opção: \n");
        printf("(1) - Usar método da Bisseccao;\n");
        printf("(2) - Usar método de Newton-Raphson;\n");
        printf("(3) - Usar método de Gauss-Seidel;\n");
        printf("(0) - Sair.\n");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            // escolher o intervalo
            printf("Digite o valor de a: ");
            scanf("%f", &a);
            printf("Digite o valor de b: ");
            scanf("%f", &b);
            // escolher o erro
            printf("Digite o valor do erro: ");
            scanf("%f", &erro);
            // conferindo os valores dados
            printf("O valor de a: %f\n", a);
            printf("O valor de b: %f\n", b);
            printf("O valor de erro: %f\n", erro);
            // chama o metodo e fornece as variaveis
            bisseccao(a, b, erro, f);
            break;
        case 2:
            // escolher valor inicial
            printf("Digite o valor de a: ");
            scanf("%f", &a);
            // escolher o erro
            printf("Digite o valor do erro: ");
            scanf("%f", &erro);
            // conferindo os valores dados
            printf("O valor de a: %f\n", a);
            printf("O valor de erro: %f\n", erro);
            // chama o metodo e fornece as variaveis
            newton_raphson(a, erro, g, dg);
            break;
        case 3:
            // escolher o tamanho da matriz
            printf("Digite o tamanho da matriz quadrada (Max %d): ", MAX);
            scanf("%d", &n);
            // escolher o erro
            printf("Digite o valor do erro: ");
            scanf("%f", &erro);
            // informar as variaveis da matriz M
            printf("LEMBRETE!!! Os valores a(i,i) devem ser diferentes de 0.\n");
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    printf("Digite o valor de a(%d,%d): ", i + 1, j + 1);
                    scanf("%f", &ma[i][j]);
                }
            }
            // informar os valores do vetor v
            for (i = 0; i < n; i++)
            {
                printf("Digite o valor de b(%d): ", i + 1);
                scanf("%f", &vb[i]);
            }
            // informar os valores iniciais de x
            for (i = 0; i < n; i++)
            {
                printf("Digite o valor de x(%d): ", i + 1);
                scanf("%f", &vx[i]);
            }
            // conferindo os valores dados
            printf("O tamanho da matriz: %d\n", n);
            printf("O valor de erro: %f\n", erro);
            printf("A matriz aumentada M + b:\n");
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    printf("%f ", ma[i][j]);
                }
                printf("| %f\n", vb[i]);
            }
            printf("Os valores inicias de x:\n");
            for (i = 0; i < n; i++)
            {
                printf("x(%d) = %f\n", i + 1, vx[i]);
            }
            // chama o metodo e fornece as variaveis
            gauss_seidel(ma, vb, vx, n, erro);
            break;
        case 0:
            printf("\n");
            printf("Saindo.\n");
            break;
        default:
            printf("\n");
            printf("Opção inválida.\n");
        }
    } while (opc != 0);
    return EXIT_SUCCESS;
}
