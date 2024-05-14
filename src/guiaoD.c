#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesAux.h"

void resertConjuntos(wchar_t arrayCartas[][60],CartaDef arrayDef[][60]){
    int i = 1;
    for(;arrayCartas[i];i++){
        if(i == 1){
            arrayCartas[1][0] = arrayCartas[0][0];
            arrayDef[1][0] = arrayDef[0][0];
            removerCartaEmBaralho(arrayCartas[0],arrayDef[0],arrayDef[0][0]);
        } else {
            for (int j = 0; j < 60; j++) {
                arrayCartas[i][j] = L'\0';
            }
        }
    }
}

void limparArrayCartaDef(CartaDef array[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        array[i].naipe = APAGADO;
        array[i].valor = 0;
    }
}

void removerMaisPequenos(wchar_t jogadasCartas[],CartaDef jogadasDef[],int tamanhoArray,int com1Sem0Naipe){
    if(com1Sem0Naipe){
        while(jogadasCartas[0] && maisPequenoCNaipe(jogadasDef[0], jogadasDef[tamanhoArray-1])){
        removerCartaEmBaralho(jogadasCartas,jogadasDef,jogadasDef[0]);
        tamanhoArray += -1;
        }
    } else {
        while(jogadasCartas[0] && maisPequenoSNaipe(jogadasDef[0], jogadasDef[tamanhoArray-1])){
        removerCartaEmBaralho(jogadasCartas,jogadasDef,jogadasDef[0]);
        tamanhoArray += -1;
        }
    }
}

// CONJUNTOS

int conjuntosPrintDRei(CartaDef ultimaJogada[],wchar_t cartas[], CartaDef def[], wchar_t printcarta[],CartaDef printdef[],int max,int counter)
{
    int control = 0, tamanho = tamanhoCartas(cartas);
    int reis = conjuntoDeReis(ultimaJogada,max);
    if((reis && tamanhoCartas(printcarta) == 4) && max == 1){
        wprintfCartas(printcarta,printdef,1);
        control++;
    } else {
        for(int i = 0; i < tamanho && (counter == 0 || printdef[0].valor == def[0].valor); i++){
            // memoria
            wchar_t cartasNEW[60] = {L'\0'};
            CartaDef defNEW[60];
            wchar_t printcartaNEW[60] = {L'\0'};
            CartaDef printdefNEW[60];
            limparArrayCartaDef(printdefNEW,60);
            limparArrayCartaDef(defNEW,60);
            wcscpy(cartasNEW, cartas);
            memcpy(defNEW, def, sizeof(CartaDef) * 60);
            wcscpy(printcartaNEW, printcarta);
            memcpy(printdefNEW, printdef, sizeof(CartaDef) * 60);
            // memoria
            printcartaNEW[counter] = cartas[0];
            printdefNEW[counter] = def[0];
            removerCartaEmBaralho(cartasNEW,defNEW,defNEW[0]);
            removerCartaEmBaralho(cartas,def,def[0]);
            control += conjuntosPrintDRei(ultimaJogada,cartasNEW,defNEW,printcartaNEW,printdefNEW,max,counter+1);
        }
    }
    return control;
}

int conjuntosPrintDNormal(CartaDef ultimaJogada[],wchar_t cartas[], CartaDef def[], wchar_t printcarta[],CartaDef printdef[],int max,int counter){
    int control = 0, tamanho = tamanhoCartas(cartas);
    if((tamanhoCartas(printcarta) == max && maisPequenoCNaipe(ultimaJogada[max-1],printdef[tamanhoCartas(printcarta)-1]))){
        wprintfCartas(printcarta,printdef,1);
        control++;
    } else {
        for(int i = 0; i < tamanho && (counter == 0 || printdef[0].valor == def[0].valor); i++){
            // memoria
            wchar_t cartasNEW[60] = {L'\0'};
            CartaDef defNEW[60];
            wchar_t printcartaNEW[60] = {L'\0'};
            CartaDef printdefNEW[60];
            limparArrayCartaDef(printdefNEW,60);
            limparArrayCartaDef(defNEW,60);
            wcscpy(cartasNEW, cartas);
            memcpy(defNEW, def, sizeof(CartaDef) * 60);
            wcscpy(printcartaNEW, printcarta);
            memcpy(printdefNEW, printdef, sizeof(CartaDef) * 60);
            // memoria
            printcartaNEW[counter] = cartas[0];
            printdefNEW[counter] = def[0];
            removerCartaEmBaralho(cartasNEW,defNEW,defNEW[0]);
            removerCartaEmBaralho(cartas,def,def[0]);
            control += conjuntosPrintDNormal(ultimaJogada,cartasNEW,defNEW,printcartaNEW,printdefNEW,max,counter+1);
        }
    }
    return control;
}

int conjuntosNormais(wchar_t jogadasCartas[][60],CartaDef jogadasDef[][60],int tamanhoArray[]){
    int control = 0;
    // memoria
    wchar_t jogarCartas[60] = {L'\0'};
    wchar_t printcarta[60] = {L'\0'};
    CartaDef ultimaJogada[60];
    CartaDef jogarDef[60];
    CartaDef printdef[60];
    limparArrayCartaDef(printdef,60);
    limparArrayCartaDef(jogarDef,60);
    wcscpy(jogarCartas, jogadasCartas[1]);
    memcpy(jogarDef, jogadasDef[1], sizeof(CartaDef) * 60);
    memcpy(ultimaJogada, jogadasDef[0], sizeof(CartaDef) * 60);
    // memoria
    control += conjuntosPrintDNormal(ultimaJogada,jogarCartas,jogarDef,printcarta,printdef,tamanhoArray[0],0);
    wchar_t jogarCartasRei[60] = {L'\0'};
    wchar_t printcartaRei[60] = {L'\0'};
    CartaDef ultimaJogadaRei[60];
    CartaDef jogarDefRei[60];
    CartaDef printdefRei[60];
    limparArrayCartaDef(printdefRei,60);
    limparArrayCartaDef(jogarDefRei,60);
    wcscpy(jogarCartasRei, jogadasCartas[1]);
    memcpy(jogarDefRei, jogadasDef[1], sizeof(CartaDef) * 60);
    memcpy(ultimaJogadaRei, jogadasDef[0], sizeof(CartaDef) * 60);
    control += conjuntosPrintDRei(ultimaJogadaRei,jogarCartasRei,jogarDefRei,printcartaRei,printdefRei,tamanhoArray[0],0);
    return control;
}

// SEQUENCIAS NORMAIS

int sequenciaPrintDNormal(CartaDef ultimaJogada[],wchar_t cartas[], CartaDef def[], wchar_t printcarta[],CartaDef printdef[],int max,int counter){
    int control = 0, tamanho = tamanhoCartas(cartas);
    if(tamanhoCartas(printcarta) == max && maisPequenoCNaipe(ultimaJogada[max-1],printdef[tamanhoCartas(printcarta)-1]) && sequenciaUnica(printdef,tamanhoCartas(printcarta))){
        wprintfCartas(printcarta,printdef,1);
        control++;
    } else {
        int i = 0;
        for(int n = i; n < tamanho && (counter != 0 && printdef[0].valor+counter != def[0].valor);n++){
            removerCartaEmBaralho(cartas,def,def[0]);
        }
        for(; i < tamanho && (counter == 0 || printdef[0].valor+counter == def[0].valor); i++){
            // memoria
            wchar_t cartasNEW[60] = {L'\0'};
            CartaDef defNEW[60];
            wchar_t printcartaNEW[60] = {L'\0'};
            CartaDef printdefNEW[60];
            limparArrayCartaDef(printdefNEW,60);
            limparArrayCartaDef(defNEW,60);
            wcscpy(cartasNEW, cartas);
            memcpy(defNEW, def, sizeof(CartaDef) * 60);
            wcscpy(printcartaNEW, printcarta);
            memcpy(printdefNEW, printdef, sizeof(CartaDef) * 60);
            // memoria
            printcartaNEW[counter] = cartas[0];
            printdefNEW[counter] = def[0];
            removerCartaEmBaralho(cartasNEW,defNEW,defNEW[0]);
            removerCartaEmBaralho(cartas,def,def[0]);
            control += sequenciaPrintDNormal(ultimaJogada,cartasNEW,defNEW,printcartaNEW,printdefNEW,max,counter+1);
        }
    }
    return control;
}

int sequenciasNormais(wchar_t jogadasCartas[][60],CartaDef jogadasDef[][60],int tamanhoArray[]){
    int control = 0;
    // memoria
    wchar_t jogarCartas[60] = {L'\0'};
    wchar_t printcarta[60] = {L'\0'};
    CartaDef ultimaJogada[60];
    CartaDef jogarDef[60];
    CartaDef printdef[60];
    limparArrayCartaDef(printdef,60);
    limparArrayCartaDef(jogarDef,60);
    wcscpy(jogarCartas, jogadasCartas[1]);
    memcpy(jogarDef, jogadasDef[1], sizeof(CartaDef) * 60);
    memcpy(ultimaJogada, jogadasDef[0], sizeof(CartaDef) * 60);
    // memoria
    control += sequenciaPrintDNormal(ultimaJogada,jogarCartas,jogarDef,printcarta,printdef,tamanhoArray[0],0);
    return control;
}

// SEQUENCIA DUPLA FUNCAO

int sequenciaDuplaPrint(CartaDef ultimaJogada[],wchar_t cartas[], CartaDef def[], wchar_t printcarta[],CartaDef printdef[],int max,int counter)
{
    int control = 0, tamanho = tamanhoCartas(cartas);
    int reis = conjuntoDeReis(ultimaJogada,max);
    if(((reis && max == 1 && tamanhoCartas(printcarta) == 6) || (reis && max == 2 && tamanhoCartas(printcarta) == 8) || (reis && max == 3 && tamanhoCartas(printcarta) == 10) || (tamanhoCartas(printcarta) == max && maisPequenoCNaipe(ultimaJogada[max-1],printdef[tamanhoCartas(printcarta)-1]))) && sequenciaDupla(printdef,tamanhoCartas(printcarta))){
        wprintfCartas(printcarta,printdef,1);
        control++;
    } else {
        int i = 0;
        for(int n = i; n < tamanho && (counter != 0 && !(counter%2) && printdef[0].valor+(counter/2) != def[0].valor);n++){
            removerCartaEmBaralho(cartas,def,def[0]);
        }
        for(; i < tamanho && (counter == 0 || printdef[0].valor+(counter/2) == def[0].valor); i++){
            // memoria
            wchar_t cartasNEW[60] = {L'\0'};
            CartaDef defNEW[60];
            wchar_t printcartaNEW[60] = {L'\0'};
            CartaDef printdefNEW[60];
            limparArrayCartaDef(printdefNEW,60);
            limparArrayCartaDef(defNEW,60);
            wcscpy(cartasNEW, cartas);
            memcpy(defNEW, def, sizeof(CartaDef) * 60);
            wcscpy(printcartaNEW, printcarta);
            memcpy(printdefNEW, printdef, sizeof(CartaDef) * 60);
            // memoria
            printcartaNEW[counter] = cartas[0];
            printdefNEW[counter] = def[0];
            removerCartaEmBaralho(cartasNEW,defNEW,defNEW[0]);
            removerCartaEmBaralho(cartas,def,def[0]);
            control += sequenciaDuplaPrint(ultimaJogada,cartasNEW,defNEW,printcartaNEW,printdefNEW,max,counter+1);
        }
    }
    return control;
}

int sequenciasDuplas(wchar_t jogadasCartas[][60],CartaDef jogadasDef[][60],int tamanhoArray[])
{
    int control = 0;
    // memoria
    wchar_t jogarCartas[60] = {L'\0'};
    wchar_t printcarta[60] = {L'\0'};
    CartaDef ultimaJogada[60];
    CartaDef jogarDef[60];
    CartaDef printdef[60];
    limparArrayCartaDef(printdef,60);
    limparArrayCartaDef(jogarDef,60);
    wcscpy(jogarCartas, jogadasCartas[1]);
    memcpy(jogarDef, jogadasDef[1], sizeof(CartaDef) * 60);
    memcpy(ultimaJogada, jogadasDef[0], sizeof(CartaDef) * 60);
    // memoria
    control += sequenciaDuplaPrint(ultimaJogada,jogarCartas,jogarDef,printcarta,printdef,tamanhoArray[0],0);
    return control;
}

// LEITURAS FUNCAO

void funcaoPirncipalD(wchar_t jogadasCartas[][60],CartaDef jogadasDef[][60],int tamanhoArray[]){
    int control = 0;
    int tipo = checkIfTrue(jogadasDef[0],tamanhoArray[0]);
    switch (tipo){
    case 1: // conjunto
        control += conjuntosNormais(jogadasCartas,jogadasDef,tamanhoArray);
        if(conjuntoDeReis(jogadasDef[0],tamanhoArray[0])){
            control += sequenciasDuplas(jogadasCartas,jogadasDef,tamanhoArray);
        }
        break;
    case 2: // sequencia
        control += sequenciasNormais(jogadasCartas,jogadasDef,tamanhoArray);
        break;
    case 3: // sequencia dupla
        control += sequenciasDuplas(jogadasCartas,jogadasDef,tamanhoArray);
        break;
    
    default:
        break;
    }
    if(control == 0) wprintf(L"PASSO\n");
}



void leituraDoGuiaoD(wchar_t jogadasCartas[][60],CartaDef jogadasDef[][60],int tamanhoArray[])
{
    int rep;
    for(rep = 0;rep < 2;rep++)
    {
        wscanf(L"%ls", jogadasCartas[rep]);
        guardarvalores(jogadasCartas[rep], jogadasDef[rep]);
        tamanhoArray[rep] = tamanhoCartas(jogadasCartas[rep]);
        ordCartaNumeroDef(jogadasCartas[rep], jogadasDef[rep], tamanhoArray[rep]);
    }
}

void funcaoGuiaoD()
{
    int leituras, repeticao;
    wscanf(L"%d\n", &leituras);
    for (repeticao = 0; repeticao < leituras; repeticao++)
    {
        wchar_t jogadasCartas[2][60];
        CartaDef jogadasDef[2][60];
        int tamanhoArray[2];
        wprintf(L"Teste %d\n", repeticao + 1);
        leituraDoGuiaoD(jogadasCartas,jogadasDef,tamanhoArray);
        funcaoPirncipalD(jogadasCartas,jogadasDef,tamanhoArray);
    }
}