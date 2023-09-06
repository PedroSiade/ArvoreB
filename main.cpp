#include<bits/stdc++.h>
#include<stdbool.h>
using namespace std;

typedef struct lista{
    bool folha;
    int dado[4]{};
    int countD;
    struct lista *filho[5], *pai{};

    lista(){
        this->folha=true;
        this->countD=0;
        for(int k=0;k<5;k++){
            if(k!=4) {
                this->dado[k] = -1;
            }
            this->filho[k]= nullptr;
        }
    }

}lista;

void split(lista *raiz, lista *no, int dado_inserido);
void splitRaiz(lista **no, int dado_inserido, lista **auxiliar);
void insertionSort(int v[], int length);
void insercao(lista **raiz, int di);
lista *busca(lista *raiz, int db, int insercao);
void remocaoFolha(lista *raiz, int dado);
void remocaoIndice(lista *raiz, int dado);
void emprestimoEsq(lista *irmao, lista *pai, lista *alvo, int dado);
void emprestimoDir(lista *irmao, lista *pai, lista *alvo, int dado);
void combinacao(lista *irmao, lista *pai, lista *alvo, int dado);
void emprestimoIndice(lista *pai, lista*irmao, lista*alvo, int dado);

int main() {
    lista *raiz = nullptr;
    insercao(&raiz, 20);
    insercao(&raiz, 40);
    insercao(&raiz, 60);
    insercao(&raiz, 80);
    insercao(&raiz, 70);
    insercao(&raiz, 10);
    insercao(&raiz, 30);
    insercao(&raiz, 15);
    insercao(&raiz, 75);
    insercao(&raiz, 85);
    insercao(&raiz, 90);
    insercao(&raiz, 25);
    insercao(&raiz, 35);
    insercao(&raiz, 50);
    insercao(&raiz, 22);
    insercao(&raiz, 27);
    remocaoFolha(raiz, 30);
    // remocaoFolha(raiz, 27);
    remocaoFolha(raiz, 25);

    return 0;
}

void remocaoIndice(lista *raiz, int dado){
    lista *alvo = NULL;
    alvo = busca(raiz, dado, 0);
    int j = 0;
    while (alvo->dado[j] != dado)
    {
        j++;
    }
    lista *irmaoEsq = alvo->pai->filho[j - 1];
    lista *irmaoPai = alvo->pai->pai->filho[j+1];
    if (alvo->filho[j]->countD > 2 && alvo->filho[j+1]->countD == 2){
        int i = 0;
        while (alvo->filho[j]->dado[i] != -1)
        {
            i++;
        }
        alvo->dado[j] = alvo->filho[j]->dado[i-1];
        alvo->filho[j]->dado[i - 1] = -1;
        insertionSort(alvo->dado, 4);
        insertionSort(alvo->filho[j]->dado, 4);
        alvo->countD--;
    }else if (alvo->filho[j]->countD == 2 && alvo->filho[j + 1]->countD > 2){
        alvo->dado[j] = alvo->filho[j+1]->dado[0];
        alvo->filho[j + 1]->dado[0] = -1;
        insertionSort(alvo->dado, 4);
        insertionSort(alvo->filho[j+1]->dado, 4);
        alvo->countD--;
    }else if (alvo->filho[j]->countD == 2 && alvo->filho[j + 1]->countD == 2 && irmaoEsq->countD > 2){
        combinacao(irmaoEsq, alvo->pai, alvo, dado);
        emprestimoIndice(alvo->pai, irmaoEsq, alvo, dado);
        alvo->countD--;
    }else if (alvo->filho[j]->countD == 2 && alvo->filho[j + 1]->countD == 2 && irmaoEsq->countD == 2){
        combinacao(irmaoEsq, alvo->pai, alvo, dado);
        combinacao(irmaoPai, alvo->pai->pai, alvo, dado);
        alvo->countD--;
    }
}

void emprestimoIndice(lista *pai, lista *irmao, lista *alvo, int dado){
    int i = 0;
    while(pai->dado[i] != -1){
        i++;
    }
    alvo->dado[3] = pai->dado[i - 1];
    int j = 0;
    while(irmao->dado[j] != -1){
        j++;
    }
    pai->dado[i-1] = irmao->dado[j-1];
    irmao->dado[j-1] = -1;
    insertionSort(pai->dado, 4);
    insertionSort(irmao->dado, 4);
    insertionSort(alvo->dado, 4);
    irmao->countD--;
}

void remocaoFolha(lista *raiz, int dado)
{
    lista *noAlvo = NULL, *noPai = NULL, *aux = NULL;
    int encontrado = 0, i = 0;
    noAlvo = busca(raiz, dado, 0);
    noPai = noAlvo->pai;
    while (noPai->dado[i] < dado)
    {
        i++;
    }

    int j = 0;
    while (noAlvo->dado[j] != dado)
    {
        j++;
    }
    if(noAlvo->countD > 2){
        noAlvo->dado[j] = -1;
        insertionSort(noAlvo->dado, 4);
        j = 0;
        int aux1 = 0, aux2 = 0;
        do
        {
            if (noAlvo->dado[j] == -1)
            {
                aux1 = noAlvo->dado[j];
                aux2 = noAlvo->dado[j + 1];
                noAlvo->dado[j] = aux2;
                noAlvo->dado[j + 1] = aux1;
                // swap(aux1, aux2);
            }
            j++;
        } while (j < 3);
        noAlvo->countD--;

    }else if(noAlvo->countD == 2){
        if(noPai->filho[i-1]->countD > 2 && noPai->filho[i+1]->countD == 2){
            emprestimoEsq(noPai->filho[i-1], noPai, noAlvo, dado);
            noAlvo->dado[j] = -1;
            insertionSort(noAlvo->dado, 4);
            noAlvo->countD--;
            j = 0;
            int aux1 = 0, aux2 = 0;
            do
            {
                if (noAlvo->dado[j] == -1)
                {
                    aux1 = noAlvo->dado[j];
                    aux2 = noAlvo->dado[j + 1];
                    noAlvo->dado[j] = aux2;
                    noAlvo->dado[j + 1] = aux1;
                    // swap(aux1, aux2);
                }
                j++;
            } while (j < 3);
        }else if (noPai->filho[i - 1]->countD == 2 && noPai->filho[i + 1]->countD > 2){
            noAlvo->dado[j] = -1;
            emprestimoDir(noPai->filho[i+1], noPai, noAlvo, dado);
            insertionSort(noAlvo->dado, 4);
            noAlvo->countD--;
            j = 0;
            int aux1 = 0, aux2 = 0;
            do
            {
                if (noAlvo->dado[j] == -1)
                {
                    aux1 = noAlvo->dado[j];
                    aux2 = noAlvo->dado[j + 1];
                    noAlvo->dado[j] = aux2;
                    noAlvo->dado[j + 1] = aux1;
                    // swap(aux1, aux2);
                }
                j++;
            } while (j < 3);
        }else if (noPai->filho[i - 1]->countD > 2 && noPai->filho[i + 1]->countD > 2){
            noAlvo->dado[j] = -1;
            emprestimoEsq(noPai->filho[i - 1], noPai, noAlvo, dado);
            insertionSort(noAlvo->dado, 4);
            noAlvo->countD--;
            j = 0;
            int aux1 = 0, aux2 = 0;
            do
            {
                if (noAlvo->dado[j] == -1)
                {
                    aux1 = noAlvo->dado[j];
                    aux2 = noAlvo->dado[j + 1];
                    noAlvo->dado[j] = aux2;
                    noAlvo->dado[j + 1] = aux1;
                    // swap(aux1, aux2);
                }
                j++;
            } while (j < 3);
        }else if (noPai->filho[i - 1]->countD == 2 && noPai->filho[i + 1]->countD == 2){
            noAlvo->dado[j] = -1;
            combinacao(noPai->filho[i - 1], noPai, noAlvo, dado);
            noAlvo->countD--;
            j = 0;
            int aux1 = 0, aux2 = 0;
            do
            {
                if (noAlvo->dado[j] == -1)
                {
                    aux1 = noAlvo->dado[j];
                    aux2 = noAlvo->dado[j + 1];
                    noAlvo->dado[j] = aux2;
                    noAlvo->dado[j + 1] = aux1;
                    // swap(aux1, aux2);
                }
                j++;
            } while (j < 3);
        }
    }
}

void combinacao(lista *irmao, lista *pai, lista *alvo, int dado){
    int i = 0, j = 0;
    while (pai->dado[i] < dado){
        i++;
    }
    alvo->dado[3] = pai->dado[i - 1];
    pai->dado[i - 1] = -1;
    insertionSort(alvo->dado, 4);
    irmao->dado[2] = alvo->dado[2];
    irmao->dado[3] = alvo->dado[3];
    do{
        pai->filho[i] = NULL;
        pai->filho[i] = pai->filho[i+1];
        i++;
    }while(i != 4);
    pai->filho[4] = NULL;
    insertionSort(pai->dado, 4);
}

void emprestimoEsq(lista *irmao, lista *pai, lista *alvo, int dado)
{
    int i = 0, j = 0;
    while(pai->dado[i] < dado){
        i++;
    }
    alvo->dado[3] = pai->dado[i-1];
    while(irmao->dado[j] != -1){
        j++;
    }
    pai->dado[i - 1] = irmao->dado[j - 1];
    irmao->dado[j - 1] = -1;
    insertionSort(irmao->dado, 4);
    insertionSort(pai->dado, 4);
}


void emprestimoDir(lista *irmao, lista *pai, lista *alvo, int dado)
{
    int i = 0;
    while (pai->dado[i] < dado)
    {
        i++;
    }
    alvo->dado[3] = pai->dado[i + 1];
    pai->dado[i + 1] = irmao->dado[0];
    irmao->dado[0] = -1;
    insertionSort(irmao->dado, 4);
    insertionSort(pai->dado, 4);
}

void insertionSort(int v[], int length){
    int temp, i, j;
    for(i = 1; i < length; i++){
        temp = v[i];

        for(j = i-1; j >=0 && v[j] > temp; j--){
            v[j+1] = v[j];
            v[j] = temp;
        }
    }
}

void split(lista **raiz, lista *no, int dado_inserido) {
    int aux[5], i, k, aux1 = 0, aux2, qtdFilho, aux3 = 0, w, filho;
    bool operador = false;
    lista *p, *Pai = nullptr, *auxliarSplit[6];
    for (i = 0; i < 5; i++) {//vetor auxiliar para ordenar o dado a fim de fazer o split
        if (i != 4)
            aux[i] = no->dado[i];
        else
            aux[i] = dado_inserido;
    }
    insertionSort(aux, 5);
    p = new lista();
    p->pai = no->pai;
    Pai = no->pai;
    qtdFilho = (Pai->countD) + 1;
    w = 0;
    while (aux3 != 1) {
        if (Pai->filho[w] == no) {
            filho = w;
            aux3 = 1;
        } else
            w++;
    }
    if (qtdFilho < 5) {
        if ((qtdFilho - 1) == filho)
            Pai->filho[filho + 1] = p;
        else {
            aux2 = 4;//posicao final do vetor
            Pai->filho[aux2] = p;
            while (aux2 != filho + 1) {//abrir espaco no vetor para alocar o filho
                if (Pai->filho[aux2 - 1] != nullptr) {
                    swap(Pai->filho[aux2 - 1], Pai->filho[aux2]);
                } else {
                    Pai->filho[aux2 - 1] = Pai->filho[aux2];
                    Pai->filho[aux2] = nullptr;
                }
                aux2--;
            }
        }
    }

    else {
        for (int a = 0; a < 5; a++) {
            auxliarSplit[a] = Pai->filho[a];
        }
        if ((qtdFilho - 1) == filho) {
            auxliarSplit[filho + 1] = p;
        } else {
            aux2 = 5;//posicao final do vetor
            auxliarSplit[aux2] = p;
            while (aux2 != filho + 1) {//abrir espaco no vetor para alocar o filho
                if (auxliarSplit[aux2 - 1] != nullptr) {
                    swap(auxliarSplit[aux2 - 1], auxliarSplit[aux2]);
                } else {
                    auxliarSplit[aux2 - 1] = auxliarSplit[aux2];
                    auxliarSplit[aux2] = nullptr;
                }
                aux2--;
            }
        }
    }
    for (k = 0; k < 5; k++) {
        if ((Pai->dado[k] < 0) && (operador == false)) {
            Pai->dado[k] = aux[2];
            insertionSort(Pai->dado, k + 1);
            operador = true;
        }
        if (k < 2) {
            no->dado[k] = aux[k];
        }
        if (k > 1)
            no->dado[k] = -1;
        if (k > 2) {
            p->dado[aux1] = aux[k];
            aux1++;
        }
    }
    if (no->folha == true) {
        p->folha = true;
    } else
        p->folha = false;
    no->countD = 2;
    Pai->countD++;
    Pai->folha = false;
    p->countD = 2;
    if(qtdFilho==5) {
        if (Pai!= *raiz) {
            split(&(*raiz), Pai, aux[2]);
        } else {
            splitRaiz(&Pai, aux[2], auxliarSplit);
            *raiz=Pai;
        }
    }

}

void splitRaiz(lista **no, int dado_inserido, lista **auxiliar) {
    int aux[5], i, k, aux1 = 0, auxFor;
    lista *p, *q;
    for (i = 0; i < 5; i++) {//vetor auxiliar para ordenar o dado a fim de fazer o split
        if (i != 4)
            aux[i] = (*no)->dado[i];
        else
            aux[i] = dado_inserido;
    }
    insertionSort(aux, 5);
    q = new lista();
    p = new lista();
    (*no)->countD=2;
    q->countD=2;
    p->countD=1;
    p->dado[0] = aux[2];
    p->filho[0] = *no;
    p->filho[1] = q;
    p->folha= false;
    for (k = 0; k < 5; k++) {
        if(k<2){
            (*no)->dado[k]=aux[k];
        }
        if (k > 1) {
            (*no)->dado[k] = -1;
        }
        if (k > 2) {
            q->dado[aux1] = aux[k];
            aux1++;
        }
    }
    auxFor=0;
    if((*auxiliar)!= nullptr){
        for(int w=0; w<6;w++){
            if(w<3){
                (*no)->filho[w]=auxiliar[w];
            }
            else{
                (*no)->filho[w]= nullptr;
                q->filho[auxFor]=auxiliar[w];
                auxFor++;
                q->filho[w]= nullptr;
            }
        }
    }
    (*no)->pai=p;
    q->pai=p;
    (*no)=p;
    (*no)->filho[0]->countD=2;
    p->countD=1;
}

void insercao(lista **raiz, int di){
    lista *p, *auxiliar=NULL;
    int k=1;
    bool operador=false;
    if(*raiz== nullptr){
        p = (lista *) malloc(sizeof(lista));
        p=new lista();
        p->dado[0]=di;
        p->countD++;
        (*raiz)=p;
    }
    else{
        p=busca(*raiz, di, 1);
        if(p->countD<4){
            while((k<4)&&(operador==false)) {
                if(p->dado[k]==-1) {
                    p->dado[k] = di;
                    operador = true;
                }
                k++;
            }
            if(k==2) {
                insertionSort(p->dado, 2);
            }
            else if(k==3){
                insertionSort(p->dado, 3);
            }
            else
                insertionSort(p->dado, 4);
            p->countD++;
        }
        else if(p!=(*raiz)){
            split(&(*raiz), p, di);
        }
        else if(p==(*raiz)){
            splitRaiz(&(*raiz), di, &auxiliar);
        }
    }
}

lista *busca(lista *raiz, int db, int insercao){
    int i, aux=0;
    lista *p=raiz;
    while(aux!=1) {
        i=0;
        while ((db > p->dado[i]) && (i < 4)&&(p->dado[i]!=-1)) {
            i++;
        }
        if(insercao==0) {
            if (p->dado[i] == db) {
                return p;
            } else if (p->filho[i] == nullptr) {
                return nullptr;
            }

        }
        else {
            if (p->folha == true) {
                return p;
            }
        }
        p = p->filho[i];
        if((i==3)&&(p->dado[i]<db)){
            p=p->filho[i+1];
        }
    }
}