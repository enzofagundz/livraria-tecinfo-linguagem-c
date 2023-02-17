//Alunos: Enzo Fagundes, Renan Vigarani e Vadson Santos

//Incluindo bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Definindo constantes para nomes de arquivos binarios

#define LIVROS "Livros.dat"
#define AUTORES "Autores.dat"
#define CATEGORIAS "Categorias.dat"
#define EDITORAS "Editoras.dat"

//Declarando structs

struct reg_livro
{
    int codigo;
    char titulo[50];
    float preco;
    int autor1;
    int autor2;
    int autor3;
    int autor4;
    int categoria;
    int editora;
    int edicao;
    char ano[5];
    int qtde;
};

struct reg_autor
{
    int codigo;
    char sobrenome[20];
    char nome[20];
};

struct reg_categoria
{
    int codigo;
    char descricao[20];
};

struct reg_editora
{
    int codigo;
    char nome[30];
    char contato[20];
    char fone[14];
    char email[20];
};

//Prototipos de funções

void cadastrarLivro();
void cadastrarAutor();
void cadastrarCategoria();
void cadastrarEditora();
void listarLivros();
void listarAutores();
void listarCategorias();
void listarEditoras();
void excluirCategoria();
void consultarPalavraChaveTitulo();
struct reg_categoria buscarCategoria(int cod);
struct reg_editora buscarEditora(int cod);
struct reg_autor buscarAutor(int cod);
struct reg_livro buscarLivro(int cod);
void consultarAutoresPeloNome();
void relatorioLivrosCategoria();
void relatorioLivrosAutor();
void relatorioEstoqueTxt();
void relatorioPrecoCategoria();

//Funções
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opc;

    //Menu para selecionar funcionalidade do programa
    do
    {
        printf("*********************************************************");
        printf("\n**                                                     **");
        printf("\n**                   Livraria Tec Info                 **");
        printf("\n**                                                     **");
        printf("\n**  1)  Cadastrar livro                                **");
        printf("\n**  2)  Cadastrar autor                                **");
        printf("\n**  3)  Cadastrar categoria                            **");
        printf("\n**  4)  Cadastrar editora                              **");
        printf("\n**  5)  Listar livros                                  **");
        printf("\n**  6)  Listar autores                                 **");
        printf("\n**  7)  Listar categorias                              **");
        printf("\n**  8)  Listar editoras                                **");
        printf("\n**  9)  Excluir categoria                              **");
        printf("\n**  10) Consultar Livro por palavra-chave              **");
        printf("\n**  11) Consultar autores pelo nome                    **");
        printf("\n**  12) Relatório de livros por categoria              **");
        printf("\n**  13) Relatório de livros de um autor                **");
        printf("\n**  14) Relatório de livros por estoque                **");
        printf("\n**  15) Relatório de livros por preço por categoria    **");
        printf("\n**  0)  Sair                                           **");

        printf("\n\n-> Opção: ");

        fflush(stdin);
        scanf("%d", &opc);

        switch(opc)
        {
        case 1:
            cadastrarLivro();//Chama a função para cadastrar livro
            break;
        case 2:
            cadastrarAutor();//Chama a função para cadastrar autor
            break;
        case 3:
            cadastrarCategoria();//Chama a função para cadastrar categoria
            break;
        case 4:
            cadastrarEditora();//Chama a função para cadastrar editora
            break;
        case 5:
            listarLivros();//Chama a função para listar livros
            break;
        case 6:
            listarAutores();//Chama a função para listar autores
            break;
        case 7:
            listarCategorias();//Chama a função para listar categorias
            break;
        case 8:
            listarEditoras();//Chama a função para listar editoras
            break;
        case 9:
            excluirCategoria();//Chama a função para excluir fisicamente uma categoria
            break;
        case 10:
            consultarPalavraChaveTitulo();//Chama a função para consultar livro através de uma palavra chave
            break;
        case 11:
            consultarAutoresPeloNome();//Chama a função para consultar autores por uma parte do nome
            break;
        case 12:
            relatorioLivrosCategoria();//chama a função para relatar todos os livros de uma categoria
            break;
        case 13:
            relatorioLivrosAutor();//Chama a função para relatar todos os livros de um autor
            break;
        case 14:
            relatorioEstoqueTxt();//Chama a funçãp para relatar todos os livros com estoque abaixo de um valor especificado
            break;
        case 15:
            relatorioPrecoCategoria();//Chama a função para relatar todos os livros mais caros de uma categoria
            break;
        case 0:
            break;
        default:
            printf("\nOpção digitada inválida! Retornando ao menu...\n\n");
            break;
        }
    }
    while(opc!=0);

}//fim main

void cadastrarLivro()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpLivros;
    struct reg_livro livro;
    struct reg_livro livroConsulta;
    char opc;
    int contAutores;

    printf("\n**                  CADASTRAR LIVRO                   **");
    printf("\n--------------------------------------------------------\n");

    //Entrada de Dados do livro

    printf("\nDigite o código do livro: ");
    fflush(stdin);
    scanf("%i", &livro.codigo);

    //Verificar se código digitado já está cadastrado
    livroConsulta = buscarLivro(livro.codigo);

    if(livroConsulta.codigo != -1)
    {
        printf("\nCódigo do livro já cadastrado!");
        printf("\nDeseja cadastrar outro código?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            printf("\n");
            return;
        }
        else
        {
            cadastrarLivro();
            return;
        }
    }

    printf("Digite o título do livro: ");
    fflush(stdin);
    gets(livro.titulo);

    printf("Digite o preço do livro: ");
    fflush(stdin);
    scanf("%f", &livro.preco);

    printf("Quantos autores o livro possui? ");
    fflush(stdin);
    scanf("%d", &contAutores);

    if(contAutores == 1)
    {
        printf("Digite o código do autor: ");
        fflush(stdin);
        scanf("%i", &livro.autor1);

        livro.autor2 = 0;
        livro.autor3 = 0;
        livro.autor4 = 0;
    }
    if(contAutores == 2)
    {
        printf("Digite o código dos dois autores: ");
        fflush(stdin);
        scanf("%i %i", &livro.autor1, &livro.autor2);

        livro.autor3 = 0;
        livro.autor4 = 0;
    }
    if(contAutores == 3)
    {
        printf("Digite o código dos três autores: ");
        fflush(stdin);
        scanf("%i %i %i", &livro.autor1, &livro.autor2, &livro.autor3);

        livro.autor4 = 0;
    }
    if(contAutores == 4)
    {
        printf("Digite o código dos quatro autores: ");
        fflush(stdin);
        scanf("%i %i %i %i", &livro.autor1, &livro.autor2, &livro.autor3, &livro.autor4);
    }

    printf("Digite o código da categoria do livro: ");
    fflush(stdin);
    scanf("%d", &livro.categoria);

    printf("Digite o código da editora do livro: ");
    fflush(stdin);
    scanf("%d", &livro.editora);

    printf("Digite a edição do livro: ");
    fflush(stdin);
    scanf("%d", &livro.edicao);

    printf("Digite o ano do livro: ");
    fflush(stdin);
    gets(livro.ano);

    printf("Digite a quantidade de exemplares do livro: ");
    fflush(stdin);
    scanf("%d", &livro.qtde);

    //Confirmar dados gravados
    printf("\n--------------------------------------------------------\n\n");
    printf("\nCódigo - %d", livro.codigo);
    printf("\nNome - %s", livro.titulo);
    printf("\nPreço - %5.2f", livro.preco);

    printf("\n\n-> Confirmar cadastro?(S/N) ");
    fflush(stdin);
    scanf("%c", &opc);

    if((opc=='N')||(opc=='n'))
    {
        printf("\nLivro não cadastrado!");
        printf("\n\nDeseja realizar cadastro novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            printf("\n");
            return;
        }
        else
        {
            cadastrarLivro();
            return;
        }
    }

    //Gravar dados digitados

    fpLivros = fopen(LIVROS, "ab");
    fwrite(&livro, sizeof(livro), 1, fpLivros);
    fclose(fpLivros);

    printf("\nLivro cadastrado com sucesso!\n\n");
}//fim cadastrarLivro

void cadastrarAutor()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpAutores;
    struct reg_autor autor;
    struct reg_autor autorConsulta;
    char opc;

    printf("\n**                   CADASTRAR AUTOR                  **");
    printf("\n--------------------------------------------------------\n");

    //Entrada de Dados do autor
    printf("\nDigite o código do autor: ");
    fflush(stdin);
    scanf("%d", &autor.codigo);

    //Verificar se código do autor já está cadastrado
    autorConsulta = buscarAutor(autor.codigo);

    if(autorConsulta.codigo != -1)
    {
        printf("\nCódigo do autor já cadastrado!");
        printf("\nDeseja cadastrar outro código?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            printf("\n");
            return;
        }
        else
        {
            cadastrarAutor();
            return;
        }
    }

    printf("Digite o sobrenome do autor: ");
    fflush(stdin);
    gets(autor.sobrenome);

    printf("Digite o nome do autor: ");
    fflush(stdin);
    gets(autor.nome);

    //Confirmar dados gravados
    printf("\n--------------------------------------------------------\n");
    printf("\nCódigo - %d", autor.codigo);
    printf("\nSobrenome - %s", autor.sobrenome);
    printf("\nNome - %s", autor.nome);

    printf("\n\n-> Confirmar cadastro?(S/N) ");
    fflush(stdin);
    scanf("%c", &opc);

    if((opc=='N')||(opc=='n'))
    {
        printf("\nAutor não cadastrado!");
        printf("\n\nDeseja realizar cadastro novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            return;
        }
        else
        {
            cadastrarAutor();
            return;
        }
    }

    //Gravar dados digitados

    fpAutores = fopen(AUTORES, "ab");
    fwrite(&autor, sizeof(autor), 1, fpAutores);
    fclose(fpAutores);

    printf("\nAutor cadastrado com sucesso!\n\n");
}//fim cadastrarAutor

void cadastrarCategoria()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpCategorias;
    struct reg_categoria categoria;
    struct reg_categoria categoriaConsulta;
    char opc;

    printf("\n**                CADASTRAR CATEGORIA                 **");
    printf("\n--------------------------------------------------------\n");

    //Entrada de Dados do autor
    printf("\nDigite o código da categoria: ");
    fflush(stdin);
    scanf("%d", &categoria.codigo);

    //Verificar se código da categoria já está cadastrado
    categoriaConsulta = buscarCategoria(categoria.codigo);

    if(categoriaConsulta.codigo != -1)
    {
        printf("\nCódigo da categoria já cadastrado!");
        printf("\nDeseja cadastrar outro código?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            printf("\n");
            return;
        }
        else
        {
            cadastrarCategoria();
            return;
        }
    }

    printf("Digite a descrição da categoria: ");
    fflush(stdin);
    gets(categoria.descricao);

    //Confirmar dados gravados
    printf("\n--------------------------------------------------------\n");
    printf("\nCódigo - %d\nDescrição - %s\n", categoria.codigo, categoria.descricao);

    printf("\n-> Confirmar cadastro?(S/N) ");
    fflush(stdin);
    scanf("%c", &opc);

    if((opc=='N')||(opc=='n'))
    {
        printf("\nCategoria não cadastrada!");
        printf("\n\nDeseja realizar cadastro novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            return;
        }
        else
        {
            cadastrarCategoria();
            return;
        }
    }

    //Gravar dados digitados

    fpCategorias = fopen(CATEGORIAS, "ab");
    fwrite(&categoria, sizeof(categoria), 1, fpCategorias);
    fclose(fpCategorias);

    printf("\nCategoria cadastrada com sucesso!\n\n");

}//fim cadastrarCategoria

void cadastrarEditora()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpEditoras;
    struct reg_editora editora, editoraConsulta;
    char opc;

    printf("\n**                CADASTRAR EDITORA                  **");
    printf("\n--------------------------------------------------------\n");

    //Entrada de Dados do autor
    printf("\nDigite o código da editora: ");
    fflush(stdin);
    scanf("%d", &editora.codigo);

    //Verificar se código da editora já está cadastrado
    editoraConsulta = buscarEditora(editora.codigo);

    if(editoraConsulta.codigo != -1)
    {
        printf("\nCódigo da editora já cadastrado!");
        printf("\nDeseja cadastrar outro código?(S/N) ");

        if((opc=='N')||(opc=='n'))
        {
            printf("\n");
            return;
        }
        else
        {
            cadastrarCategoria();
            return;
        }
    }

    printf("Digite o nome da editora: ");
    fflush(stdin);
    gets(editora.nome);

    printf("Digite um nome para contato: ");
    fflush(stdin);
    gets(editora.contato);

    printf("Digite o número de telefone da editora: ");
    fflush(stdin);
    gets(editora.fone);

    printf("Digite o email da editora: ");
    fflush(stdin);
    gets(editora.email);

    //Confirmar dados gravados
    printf("\n--------------------------------------------------------\n");
    printf("\nCódigo - %d", editora.codigo);
    printf("\nNome - %s", editora.nome);
    printf("\nContato - %s", editora.contato);
    printf("\nTelefone - %s", editora.fone);
    printf("\nEmail - %s\n", editora.email);

    printf("\n-> Confirmar cadastro?(S/N) ");
    fflush(stdin);
    scanf("%c", &opc);

    if((opc=='N')||(opc=='n'))
    {
        printf("\nEditora não cadastrada!");
        printf("\n\nDeseja realizar cadastro novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);
        if((opc=='N')||(opc=='n'))
        {
            return;
        }
        else
        {
            cadastrarCategoria();
            return;
        }
    }

    //Gravar dados digitados

    fpEditoras = fopen(EDITORAS, "ab");
    fwrite(&editora, sizeof(editora), 1, fpEditoras);
    fclose(fpEditoras);

    printf("\nEditora cadastrada com sucesso!\n\n");

}//fim cadastrarEditora

void listarLivros()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpLivros;
    struct reg_livro livro;

    printf("\n**                   LISTAR LIVROS                    **\n");
    printf("\n--------------------------------------------------------\n");

    //Abrir arquivo para leitura

    fpLivros = fopen(LIVROS, "rb");

    //Selecionar e imprimir dados

    while(fread(&livro, sizeof(livro), 1, fpLivros)==1)
    {
        printf("\nCódigo - %d", livro.codigo);
        printf("\nTítulo - %s", livro.titulo);
        printf("\nPreço - %5.2f", livro.preco);
        printf("\nCódigo Autor 1 - %d", livro.autor1);
        printf("\nCódigo Autor 2 - %d", livro.autor2);
        printf("\nCódigo Autor 3 - %d", livro.autor3);
        printf("\nCódigo Autor 4 - %d", livro.autor4);
        printf("\nCategoria - %d", livro.categoria);
        printf("\nAno - %s", livro.ano);
        printf("\nQuantidade - %d", livro.qtde);

        printf("\n\n--------------------------------------------------------\n");
    }

    printf("\n");
    fclose(fpLivros);

}//fim listarLivros

void listarAutores()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpAutores;
    struct reg_autor autor;

    printf("\n**                   LISTAR AUTORES                   **\n");
    printf("\n--------------------------------------------------------\n");
    //Abrir arquivo para leitura

    fpAutores = fopen(AUTORES, "rb");

    //Selecionar e imprimir dados

    while(fread(&autor, sizeof(autor), 1, fpAutores)==1)
    {
        printf("\nCódigo - %d", autor.codigo);
        printf("\nSobrenome - %s", autor.sobrenome);
        printf("\nNome - %s", autor.nome);

        printf("\n\n--------------------------------------------------------\n");
    }

    printf("\n");
    fclose(fpAutores);

}//fim listarAutores

void listarCategorias()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpCategorias;
    struct reg_categoria categoria;

    printf("\n**                  LISTAR CATEGORIAS                 **\n");
    printf("\n--------------------------------------------------------\n");
    //Abrir arquivo para leitura

    fpCategorias = fopen(CATEGORIAS, "rb");

    //Selecionar e imprimir dados

    while(fread(&categoria, sizeof(categoria), 1, fpCategorias)==1)
    {
        printf("\nCódigo - %d", categoria.codigo);
        printf("\nCategoria - %s", categoria.descricao);

        printf("\n\n--------------------------------------------------------\n");
    }

    printf("\n");
    fclose(fpCategorias);

}//fim listarCategorias

void listarEditoras()
{
    //Declarando ponteiros, structs e variáveis

    FILE *fpEditoras;
    struct reg_editora editora;

    printf("\n**                   LISTAR EDITORAS                  **\n");
    printf("\n--------------------------------------------------------\n");
    //Abrir arquivo para leitura

    fpEditoras = fopen(EDITORAS, "rb");

    //Selecionar e imprimir dados

    while(fread(&editora, sizeof(editora), 1, fpEditoras)==1)
    {
        printf("\nCódigo - %d", editora.codigo);
        printf("\nNome - %s", editora.nome);
        printf("\nContato - %s", editora.contato);
        printf("\nFone - %s", editora.fone);
        printf("\nEmail - %s", editora.email);

        printf("\n\n--------------------------------------------------------\n");
    }

    printf("\n");
    fclose(fpEditoras);

}//fim listarEditoras

void excluirCategoria()
{
    //Declarando arquivos, structs e variáveis
    FILE *fpCategorias, *fpCategoriasNovo;
    struct reg_categoria categoria;
    int cod, achou=0;
    char opc;

    printf("\n**                  EXCLUIR CATEGORIA                 **\n");
    printf("\n--------------------------------------------------------\n");

    //Entrada de dados para exclusão

    printf("\nDigite o código da categoria que será excluída: ");
    fflush(stdin);
    scanf("%d",&cod);

    fpCategorias = fopen(CATEGORIAS,"rb");

    //Encontrar categoria
    while ((achou==0)&&(fread(&categoria, sizeof(categoria), 1, fpCategorias)==1))
    {
        if (categoria.codigo==cod)  //Encontrou a categoria
        {
            printf("\nCódigo - %d", categoria.codigo);
            printf("\nDescrição - %s", categoria.descricao);

            printf("\n\n--------------------------------------------------------\n");

            achou=1;
        }
    }

    fclose(fpCategorias);

    //Verificar se categoria NÃO foi localizada
    if (achou==0)
    {

        printf("\nCategoria não Localizada!!");
        printf("\n\nDeseja digitar o código novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);

        if((opc=='s')||(opc=='S'))
        {
            //Abre a função novamente e depois de executar volta ao menu principal
            excluirCategoria();
            return;
        }
        else
        {
            return;//Retorna ao menu principal
        }
    }

    //Caso o autor seja localizado

    printf("\nConfirmar categoria?(S/N) ");
    fflush(stdin);
    scanf("%c", &opc);

    if ((opc=='N')||(opc=='n'))
    {
        printf("\nCategoria não confirmado!");
        printf("\n\nDeseja digitar o código novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);

        if((opc=='S')||(opc=='s'))
        {
            //Abre a função novamente e depois de executar volta ao menu principal
            excluirCategoria();
            return;
        }
        else
        {
            return; //Retorna ao menu principal
        }
    }

    //Categoria Confirmada - confirmar a exclusão

    printf("\nExcluir categoria?(S/N) ");
    fflush(stdin);
    scanf("%c",&opc);

    if ((opc=='N')||(opc=='n'))
    {
        printf("\nExclusão Cancelada!");
        printf("\n\nDeseja digitar o código novamente?(S/N) ");
        fflush(stdin);
        scanf("%c", &opc);

        if((opc=='S')||(opc=='s'))
        {
            //Abre a função novamente e depois de executar volta ao menu principal
            excluirCategoria();
            return;
        }
        else
        {
            return; //Retorna ao menu principal
        }
    }

    //Exclusao Confirmada - Excluir Fisicamente

    fpCategorias = fopen(CATEGORIAS,"rb");
    fpCategoriasNovo = fopen("Categoriasnew.dat","wb");

    while(fread(&categoria, sizeof(categoria), 1, fpCategorias)==1)
    {
        if (categoria.codigo!=cod)
        {
            fwrite(&categoria, sizeof(categoria), 1, fpCategoriasNovo); //grava no novo arquivo
        }
    }

    fclose(fpCategorias);
    fclose(fpCategoriasNovo);

    system("del Categorias.dat");
    system("ren Categoriasnew.dat Categorias.dat");

    printf("\nCategoria excluída com sucesso!\n\n");

}//Fim excluirCategoria

void consultarPalavraChaveTitulo()
{
    //Declaração de ponteiros, structs e variáveis

    FILE *fpLivros;
    //Todas as structs estão declaradas para realizar a busca das informações do livro
    struct reg_livro livro;
    struct reg_autor autor;
    struct reg_categoria categoria;
    struct reg_editora editora;

    char palavra[30];
    int achou=0; //Variável flag

    printf("\n**               CONSULTAR PALAVRA-CHAVE              **\n");
    printf("\n--------------------------------------------------------\n");

    //Entrada de dados

    printf("\nDigite a Palavra-Chave: ");
    fflush(stdin);
    gets(palavra);

    fpLivros = fopen(LIVROS,"rb");

    //Laço para percorrer o arquivo binário fpLivros

    while (fread(&livro, sizeof(livro), 1, fpLivros)==1)
    {
        //Condicional para verificar substring 'palavra' dentro da string 'livro.titulo'
        if (strstr(livro.titulo, palavra)!=NULL)  //Achou
        {
            categoria = buscarCategoria(livro.categoria);//Busca o nome da categoria
            editora = buscarEditora(livro.editora);//Busca o nome da editora

            //Saída de dados
            printf("\nCódigo - %d", livro.codigo);
            printf("\nTítulo - %s", livro.titulo);
            printf("\nPreço - %5.2f", livro.preco);
            autor = buscarAutor(livro.autor1);//Busca o nome do autor1
            printf("\nAutor 1 - %s %s", autor.nome, autor.sobrenome);

            //Verificar se o livro possui dois autores
            if(livro.autor2!=0)
            {
                autor = buscarAutor(livro.autor2); //Enviar o código do autor2
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro três autores
            if(livro.autor3!=0)
            {
                autor = buscarAutor(livro.autor3);//Enviar o código do autor3
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro possui quatro autores
            if(livro.autor4!=0)
            {
                autor = buscarAutor(livro.autor4);//Enviar o código do autor4
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            printf("\nCategoria - %s", categoria.descricao);
            printf("\nEditora - %s", editora.nome);
            printf("\nAno - %s", livro.ano);
            printf("\nQuantidade - %d", livro.qtde);

            printf("\n\n--------------------------------------------------------\n");

            achou=1;
        }
    }

    if (achou==0)
        printf("\nNenhum Livro com esta Palavra-chave foi Localizado!!");

    fclose(fpLivros);
}//Fim consultarPalavraChaveTitulo

struct reg_livro buscarLivro(int cod)//Recebe o código do livro
{
    //Declaração de ponteiros, structs e variáveis
    FILE *fpLivros;
    struct reg_livro livro;
    int achou=0;//Variável flag

    fpLivros = fopen(LIVROS,"rb");

    //Laço de repetição para percorrer o arquivo binário fpLivros
    while ((achou == 0) && (fread(&livro, sizeof(livro), 1, fpLivros)==1))
    {
        //Condicional para verificar se o código de algum livro do arquivo é igual ao recebido pela função
        if (livro.codigo == cod)  //Achou
        {
            achou = 1;
        }
    }

    fclose(fpLivros);

    //Condicional para retornar um código de livro inexistente a função que a chamou
    if (achou == 0)
    {
        livro.codigo = -1;
    }

    return livro; //Retornando a struct livro

}//fim buscarLivro

struct reg_categoria buscarCategoria(int cod)//Recebe o código da categoria
{
    //Declaração de ponteiros, structs e variáveis
    FILE *fpCategorias;
    struct reg_categoria categoria;
    int achou = 0;

    fpCategorias = fopen(CATEGORIAS,"rb");

    //Laço de repetição para percorrer o arquivo binário fpCategorias
    while ((achou == 0) && (fread(&categoria, sizeof(categoria), 1, fpCategorias)==1))
    {
        //Condicional para verificar se o código de alguma categoria do arquivo é igual ao recebido pela função
        if (categoria.codigo == cod)  //Achou
        {
            achou = 1;
        }
    }

    fclose(fpCategorias);

    //Condicional para retornar um código de categoria inexistente a função que a chamou
    if (achou == 0)
    {
        categoria.codigo = -1;
    }

    return categoria;

}//fim buscarCategoria

struct reg_editora buscarEditora(int cod)//Recebe o código da Editora
{
    //Declaração de ponteiros, structs e variáveis
    FILE *fpEditoras;
    struct reg_editora editora;
    int achou=0;

    fpEditoras = fopen(EDITORAS,"rb");

    //Laço de repetição para percorrer o arquivo binário fpEditoras
    while ((achou == 0) && (fread(&editora, sizeof(editora), 1, fpEditoras)==1))
    {
        //Condicional para verificar se o código de alguma editora do arquivo é igual ao recebido pela função
        if (editora.codigo == cod)  //Achou
        {
            achou = 1;
        }
    }

    fclose(fpEditoras);

    //Condicional para retornar um código de editora inexistente a função que a chamou
    if (achou == 0)
    {
        editora.codigo = -1;
    }

    return editora;

}//fim buscarEditora

struct reg_autor buscarAutor(int cod)//Recebe o código do autor
{
    //Declaração de ponteiros, structs e variáveis
    FILE *fpAutores;
    struct reg_autor autor;
    int achou=0;

    fpAutores = fopen(AUTORES,"rb");

    //Laço de repetição para percorrer o arquivo binário fpAutores
    while ((achou == 0) && (fread(&autor, sizeof(autor), 1, fpAutores)==1))
    {
        //Condicional para verificar se o código de algum autor do arquivo é igual ao recebido pela função
        if (autor.codigo == cod)  //Achou
        {
            achou = 1;
        }
    }

    fclose(fpAutores);

    //Condicional para retornar um código de autor inexistente a função que a chamou
    if (achou == 0)
    {
        autor.codigo = -1;
    }

    return autor;

}//fim buscarNomeAutor

void consultarAutoresPeloNome()
{
    //Declaração de ponteiros, structs e variáveis
    FILE *fpAutores;
    struct reg_autor autor;
    char nome[20];
    int achou = 0;//Variável flag

    //Entrada de dados
    printf("\nDigite o nome do autor a ser Localizado: ");
    fflush(stdin);
    gets(nome);

    fpAutores = fopen(AUTORES,"rb");

    //Laço de repetição para percorrer o arquivo binário fpAutores
    while ((achou == 0) && (fread(&autor, sizeof(autor), 1, fpAutores)==1))
    {
        //Condicional para comparar se alguma substring do arquivo fpAutores é igual ao conteúdo da variavel 'nome'
        if (strstr(autor.nome, nome)!=NULL)  //Achou
        {
            //Saída de dados
            printf("\nCódigo - %d", autor.codigo);
            printf("\nNome - %s", autor.nome);
            printf("\nSobrenome - %s\n\n", autor.sobrenome);
            achou = 1;//Varíavel flag usada para parar o laço
        }
    }

    //Condicional para verificar se variável flag foi alterada
    if (achou == 0)
    {
        printf("\nAutor não localizado!\n\n");
    }

    fclose(fpAutores);

}//fim consultarAutoresPeloNome

void relatorioLivrosCategoria()
{
    //Declaração de ponteiros, structs e variáveis

    FILE *fpLivros, *fpCategorias;
    //As structs declaradas para realizarão consulta das informações presentes em livros
    struct reg_livro livro;
    struct reg_autor autor;
    struct reg_categoria categoria;
    struct reg_editora editora;
    int achou=0, opc; //Variável flag

    printf("\n**           RELATÓRIO LIVROS POR CATEGORIA           **\n");
    printf("\n--------------------------------------------------------\n");

    fpCategorias = fopen(CATEGORIAS, "rb");

    //Listando as categorias cadastradas para o usuário

    printf("\nCódigo          Categoria\n");
    while(fread(&categoria, sizeof(categoria), 1, fpCategorias)==1)
    {
        printf("\n%d               %s", categoria.codigo, categoria.descricao);
        printf("\n--------------------------------------------------------");
    }

    fclose(fpCategorias);

    //Entrada de dados

    printf("\n\n-> Selecione o código da categoria: ");
    fflush(stdin);
    scanf("%d", &opc);

    fpLivros = fopen(LIVROS,"rb");
    categoria = buscarCategoria(opc);//Busca o inicial da categoria

    //Laço para percorrer o arquivo binário fpLivros

    while(fread(&livro, sizeof(livro), 1, fpLivros)==1)
    {
        //Condicional para verificar se código digitado é igual ao de algum livro
        if (livro.categoria==opc)  //Achou
        {
            editora = buscarEditora(livro.editora);//Busca o nome da editora
            autor = buscarAutor(livro.autor1);//Busca o nome do primeiro autor

            //Saída de dados
            printf("\nCódigo - %d", livro.codigo);
            printf("\nTítulo - %s", livro.titulo);
            printf("\nPreço - %5.2f", livro.preco);
            printf("\nAutor 1 - %s %s", autor.nome, autor.sobrenome);

            //Verificar se o livro possui dois autores
            if(livro.autor2!=0)
            {
                autor = buscarAutor(livro.autor2); //Enviar o código do autor2
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro três autores
            if(livro.autor3!=0)
            {
                autor = buscarAutor(livro.autor3);//Enviar o código do autor3
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro possui quatro autores
            if(livro.autor4!=0)
            {
                autor = buscarAutor(livro.autor4);//Enviar o código do autor4
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            printf("\nCategoria - %s", categoria.descricao);
            printf("\nEditora - %s", editora.nome);
            printf("\nEdição - %d", livro.edicao);
            printf("\nAno - %s", livro.ano);
            printf("\nQuantidade - %d", livro.qtde);

            printf("\n\n--------------------------------------------------------\n\n");

            achou=1;
        }
    }

    if (achou==0)
        printf("\nNenhum Livro com esta Categoria foi Localizado!!\n\n");

    fclose(fpLivros);

}//fim relatorioLivrosCategoria

void relatorioLivrosAutor()
{
    //Declaração de ponteiros, structs e variáveis

    FILE *fpLivros, *fpAutores;
    //As structs declaradas para realizarão consulta das informações presentes em livros
    struct reg_livro livro;
    struct reg_autor autor;
    struct reg_categoria categoria;
    struct reg_editora editora;
    int achou=0, opc; //Variável flag

    printf("\n**             RELATÓRIO LIVROS POR AUT OR            **\n");
    printf("\n--------------------------------------------------------\n");

    fpAutores = fopen(AUTORES, "rb");

    //Listando os autores cadastrados para o usuário

    printf("\nCódigo          Nome\n");
    while(fread(&autor, sizeof(autor), 1, fpAutores)==1)
    {
        printf("\n%d               %s %s", autor.codigo, autor.nome, autor.sobrenome);
        printf("\n--------------------------------------------------------");
    }

    fclose(fpAutores);

    //Entrada de dados

    printf("\n\n-> Selecione o código do autor: ");
    fflush(stdin);
    scanf("%d", &opc);

    autor = buscarAutor(opc);//Realizando busca inicial do autor

    fpLivros = fopen(LIVROS,"rb");

    //Laço para percorrer o arquivo binário fpLivros

    while(fread(&livro, sizeof(livro), 1, fpLivros)==1)
    {
        //Condicional para verificar se código digitado de um autor está presente em algum livro
        if ((livro.autor1==opc))  //Achou
        {
            categoria = buscarCategoria(opc);//Busca o nome da categoria
            editora = buscarEditora(livro.editora);//Busca o nome da editora

            //Saída de dados
            printf("\nCódigo - %d", livro.codigo);
            printf("\nTítulo - %s", livro.titulo);
            printf("\nPreço - %5.2f", livro.preco);
            printf("\nCategoria - %s", categoria.descricao);
            printf("\nAutor 1 - %s %s", autor.nome, autor.sobrenome);

            //Verificar se o livro possui dois autores
            if((livro.autor2!=0))
            {
                autor = buscarAutor(livro.autor2); //Enviar o código do autor2
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro três autores
            if(livro.autor3!=0)
            {
                autor = buscarAutor(livro.autor3);//Enviar o código do autor3
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro possui quatro autores
            if(livro.autor4!=0)
            {
                autor = buscarAutor(livro.autor4);//Enviar o código do autor4
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            printf("\nEditora - %s", editora.nome);
            printf("\nEdição - %d", livro.edicao);
            printf("\nAno - %s", livro.ano);
            printf("\nQuantidade - %d", livro.qtde);

            printf("\n\n--------------------------------------------------------\n\n");

            achou=1;
        }
    }

    if (achou==0)
        printf("\nNenhum Livro deste Autor foi Localizado!!\n\n");

    fclose(fpLivros);

}//fim relatorioLivrosAutor

void relatorioEstoqueTxt()
{
    //Declarando ponteiros, structs e variáveis
    FILE *fpLivros, *fpLivrosTxt;
    struct reg_livro livro;
    struct reg_autor autor;
    struct reg_categoria categoria;
    struct reg_editora editora;
    int qtde, achou=0;
    char saida[100];

    //Abrir arquivos

    fpLivrosTxt = fopen("RelatorioEstoqueLivros.txt", "w");
    fpLivros = fopen(LIVROS, "rb");

    fputs("\n**            RELATÓRIO LIVROS POR ESTOQUE            **\n", fpLivrosTxt);
    fputs("\n--------------------------------------------------------\n", fpLivrosTxt);


    //Pedir quantidade de livros para verficar o estoque

    printf("\nDigite a quantidade em estoque para verificar: ");
    fflush(stdin);
    scanf("%d", &qtde);

    //Percorrer arquivo fpLivros com um laço

    fputs("\nCodigo                   Titulo                            Autor  Categoria  Editora  Edição   Ano  Qtde", fpLivrosTxt);

    while(fread(&livro, sizeof(livro), 1, fpLivros)==1)
    {
        //Condicional para verificar se a quantidade digitada é igual ou maior a de algum livro
        if(livro.qtde<=qtde)  //Achou
        {
            editora = buscarEditora(livro.editora);//Busca o nome da editora
            autor = buscarAutor(livro.autor1);//Busca o nome do primeiro autor
            categoria = buscarCategoria(livro.categoria);//Busca o nome da categoria

            //Saída de dados
            printf("\nCódigo - %d", livro.codigo);
            printf("\nTítulo - %s", livro.titulo);
            printf("\nPreço - %5.2f", livro.preco);
            printf("\nAutor 1 - %s %s", autor.nome, autor.sobrenome);

            //Verificar se o livro possui dois autores
            if(livro.autor2!=0)
            {
                autor = buscarAutor(livro.autor2); //Enviar o código do autor2
                printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro três autores
            if(livro.autor3!=0)
            {
                autor = buscarAutor(livro.autor3);//Enviar o código do autor3
                printf("\nAutor 3 - %s %s", autor.nome, autor.sobrenome);
            }

            //Verificar se o livro possui quatro autores
            if(livro.autor4!=0)
            {
                autor = buscarAutor(livro.autor4);//Enviar o código do autor4
                printf("\nAutor 4 - %s %s", autor.nome, autor.sobrenome);
            }

            printf("\nCategoria - %s", categoria.descricao);
            printf("\nEditora - %s", editora.nome);
            printf("\nEdição - %d", livro.edicao);
            printf("\nAno - %s", livro.ano);
            printf("\nQuantidade - %d", livro.qtde);

            printf("\n\n--------------------------------------------------------\n");

            //Imprimir os livros com sprintf em um arquivo txt

            sprintf(saida, "\n%-5d                    %s %5d %5d %5d %5d %5s %5d", livro.codigo, livro.titulo, livro.autor1, livro.categoria, livro.editora, livro.edicao, livro.ano, livro.qtde);
            fputs(saida, fpLivrosTxt);

            achou=1;
        }
    }

    //Fechar arquivos
    fclose(fpLivros);
    fclose(fpLivrosTxt);

    if (achou==0)
    {
        printf("\nNenhum Livro com esta quantidade localizado!\n\n");
    }
    else
    {
        printf("\nRelatorio em TXT gerado com Sucesso.\n\n");
    }

}//fim relatorioEstoqueTxt

void relatorioPrecoCategoria()
{
    //Declaração de ponteiros, structs e variáveis

    FILE *fpLivros, *fpCategorias;
    //As structs declaradas para realizarão consulta das informações presentes em livros
    struct reg_livro livro;
    struct reg_autor autor;
    struct reg_categoria categoria;
    struct reg_editora editora;
    int achou=0, opc, codigo=0; //Variável flag
    float maior=0.0, maiorAux=0.0;

    printf("\n**           RELATÓRIO LIVROS POR CATEGORIA           **\n");
    printf("\n--------------------------------------------------------\n");

    fpCategorias = fopen(CATEGORIAS, "rb");

    //Listando as categorias cadastradas para o usuário

    printf("\nCódigo          Categoria\n");
    while(fread(&categoria, sizeof(categoria), 1, fpCategorias)==1)
    {
        printf("\n%d               %s", categoria.codigo, categoria.descricao);
        printf("\n--------------------------------------------------------");
    }

    fclose(fpCategorias);

    //Entrada de dados

    printf("\n\n-> Selecione o código da categoria: ");
    fflush(stdin);
    scanf("%d", &opc);

    fpLivros = fopen(LIVROS,"rb");
    categoria = buscarCategoria(opc);//Busca inicial da categoria

    //Laço para percorrer o arquivo binário fpLivros

    while(fread(&livro, sizeof(livro), 1, fpLivros)==1)
    {
        if (livro.categoria==opc)
        {
            maior = livro.preco;

            //Condicional para verificar se código digitado é igual ao de algum livro
            if (maior > maiorAux)
            {
                maiorAux = maior;
                codigo = livro.codigo;
            }
        }
    }

    livro = buscarLivro(codigo);
    editora = buscarEditora(livro.editora);//Busca o nome da editora
    autor = buscarAutor(livro.autor1);//Busca o nome do primeiro autor

    //Saída de dados
    printf("\nCódigo - %d", livro.codigo);
    printf("\nTítulo - %s", livro.titulo);
    printf("\nPreço - %5.2f", livro.preco);
    printf("\nAutor 1 - %s %s", autor.nome, autor.sobrenome);

    //Verificar se o livro possui dois autores
    if(livro.autor2!=0)
    {
        autor = buscarAutor(livro.autor2); //Enviar o código do autor2
        printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
    }

    //Verificar se o livro três autores
    if(livro.autor3!=0)
    {
        autor = buscarAutor(livro.autor3);//Enviar o código do autor3
        printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
    }

    //Verificar se o livro possui quatro autores
    if(livro.autor4!=0)
    {
        autor = buscarAutor(livro.autor4);//Enviar o código do autor4
        printf("\nAutor 2 - %s %s", autor.nome, autor.sobrenome);
    }

    printf("\nCategoria - %s", categoria.descricao);
    printf("\nEditora - %s", editora.nome);
    printf("\nEdição - %d", livro.edicao);
    printf("\nAno - %s", livro.ano);
    printf("\nQuantidade - %d", livro.qtde);

    printf("\n\n--------------------------------------------------------\n\n");

    fclose(fpLivros);

}//fim relatorioPrecoCategoria

