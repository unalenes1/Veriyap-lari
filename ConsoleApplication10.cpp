#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <clocale>
#include <ctime>
#include <time.h>
using namespace std;

#define MIN(x,y) ((x) < (y) ? (x) : (y))
string _gelen;
int i, j  , l1, l2, t, track;
char txt[100000000];
char html[100000000];
char rtf[100000000];
char xml[100000000];
int sayac = 0;
int sayact = 0; 
#define MAX 100
static int mesafe;



#pragma region levenshtein
int MinimumBul(int a, int b, int c)
{
    int minimum = a;
    if (b <= minimum)
        minimum = b;
    if (c <= minimum)
        minimum = c;
    return minimum;
}

int levenshtein(char GK[], char KK[], int m, int n)
{
    int Matris[MAX][MAX];
    for (int i = 0; i < m; i++)
        Matris[i][0] = i;
    for (int i = 0; i < n; i++)
        Matris[0][i] = i;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (GK[i - 1] == KK[j - 1])
            {
                Matris[i][j] = Matris[i - 1][j - 1];
                mesafe = Matris[i][j];
            }
            else
            {
                Matris[i][j] = MinimumBul(Matris[i - 1][j] + 1, Matris[i][j - 1] + 1, Matris[i - 1][j - 1] + 1);
                mesafe = Matris[i][j];
            }
        }
    }
    return mesafe;
}

#pragma endregion

#pragma region karprabin Algoritma
// d is the number of characters in the input alphabet  
#define d 256  

/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(char pat[], char txt[], int q , int sayi)
{
   

    int M = strlen(pat);
    int N = strlen(txt);
    int p = 0; // hash value for pattern  
    int t = 0; // hash value for txt  
    int h = 1;

    ofstream dosya("aranan_" + string(pat) + ".txt", ios::out | ios::app);
    // The value of h would be "pow(d, M-1)%q"  
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first  
    // window of text  
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    cout<<endl<<"--------------------------------> " <<"Aranan Kelime : "<< pat << " <-------------------------------" << endl;
    // Slide the pattern over text one by one  
    for (i = 0; i <= N - M; i++)
    {
        
        // Check the hash values of current window of text  
        // and pattern. If the hash values match then only  
        // check for characters on by one  
        if (p == t)
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]  
            if (j == M) {
            if (sayi == 1)
                _gelen = "RTF";
            if (sayi == 2)
                _gelen = "TXT";
            if (sayi == 3)
                _gelen = "HTML";
            if (sayi == 4)
                _gelen = "XML";
            dosya << "Aranan Tür : " << _gelen << endl << "Bulundugu Indis : " << i << endl;
            cout << "Bulundugu index " << i << sayact++ << sayac++ << endl;
         }
        }
        // Calculate hash value for next window of text: Remove  
        // leading digit, add trailing digit  
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting it  
            // to positive  
            if (t < 0)
                t = (t + q);

        }
        if (i == N-M && j != M) {
            cout <<endl<< "Sonuc Bulunamadi :("<<endl<<endl;

        }

    }
}
#pragma endregion

#pragma region txt
void veriCekTxt() {

   
    fstream oku;
    oku.open("veri.txt");

    if (oku.is_open())
    {


            for (int i = 0; i < 1000000; ++i)
            {
                oku >> txt[i];
            }

        
    }
}
#pragma endregion

#pragma region Html 
bool InTag(char c)
{
    static int bracket = 0;
    switch (c)
    {
    case '<':
        ++bracket;
        break;
    case '>':
        --bracket;
        return true;
    }
    return bracket > 0;
}

void htmlcek() {



    ifstream myfile("veri.html");
    if (myfile.is_open())
    {
        for (int i = 0; i < 1000000; ++i)
            myfile >> html[i];

        myfile.close();
    }

}
#pragma endregion

#pragma region RTF

void rtfcek() {

    string line; //this will contain the data read from the file
    ifstream myfile("veri.rtf"); //opening the file.
    if (myfile.is_open()) //if the file is open
    {
        for (int i = 0; i < 1000000; ++i)
            myfile >> rtf[i];

        myfile.close(); //closing the file
    }
    else cout << "Unable to open file";
}
#pragma endregion

#pragma region xml
void xmlCek() {


    fstream oku;
    oku.open("veri.xml");

    if (oku.is_open())
    {


        for (int i = 0; i < 1000000; ++i)
        {
            oku >> xml[i];
        }


    }
}
#pragma endregion



int main()
{
 

    
    int j = 101; // A prime number  
    int z = 10;
    char pat[256] ;
    int secim;
    setlocale(LC_ALL, "Turkish");
    srand(time(0));
    clock_t t1, t2,t3, t4, t5, t6, t7, t8, t9, t10;
    t9 = clock();

    cout << "Aranacak Kelimeyi Giriniz : ";
    cin.getline(pat,256);
    static char GirilenKelime[MAX];
    char KayitliKelime[MAX];
    string kelimler[13] = { "veri", "Data", "DataBase", "oracle", "system", "Program" , "Objects" , "Data Access" , "Data Access" , "Insert" , "update" , "delete" , "table" };


    for (int i = 0; i < MAX; i++)
    {
        pat[i] = tolower(pat[i]);
    }

    for (int i = 0; i < 13; i++)
    {
        char* KayitliKelime = (char*)kelimler[i].c_str();
        int mesafe = levenshtein(pat, KayitliKelime, ((int)strlen(pat) + 1), ((int)strlen(KayitliKelime) + 1));

        if ((int)strlen(pat) <= 20 && mesafe <= 4)
            cout << "Bunu mu demek istediniz?" << kelimler[i] << endl;
    }
    system("pause");


    t1 = clock();
    cout << " ========== XML den Cekme Islemi Basliyor ========== " << endl;
    xmlCek();
    search(pat, xml, j,1);
    cout<<"--> XML de " << sayac<<" Sonuc Bulundu  <--"<<endl;
    t2 = clock();
    float s1 = t1, s2 = t2;
    cout << "XML Arama işleminin çalışma süresi " << (s2 - s1) / 1000 << " saniye" << endl;
    cout << "========== XML Den Cekme Islemi Bitti ==========" << endl << endl;


    t3 = clock();
    sayac = 0;
    cout << " ========== RTF den Cekme Islemi Basliyor ========== " << endl;
    rtfcek();
    search(pat, rtf, j,2);
    cout << "--> RTF de " << sayac << " Sonuc Bulundu  <--" << endl;
    t4 = clock();
    float s3 = t3, s4 = t4;
    cout << "RTF Arama işleminin çalışma süresi " << (s4 - s3) / 1000 << " saniye" << endl;
    cout << "========== RTF Den Cekme Islemi Bitti ==========" << endl << endl;


    t5 = clock();
    sayac = 0;
    cout << " ========== Html den Cekme Islemi Basliyor ========== " << endl;
    htmlcek();
    search(pat, html, j,3);
    cout << "--> Html de " << sayac << " Sonuc Bulundu  <--" << endl;
    t6 = clock();
    float s5 = t5, s6 = t6;
    cout << "Html Arama işleminin çalışma süresi " << (s6 - s5) / 1000 << " saniye" << endl;
    cout << "========== Html Den Cekme Islemi Bitti =========="<<endl << endl;


    t7 = clock();
    sayac = 0;
    cout << " ========== TXT den Cekme Islemi Basliyor ========== " << endl;
    veriCekTxt();
    search(pat, txt, j,4);
    cout << "--> TXT de " << sayac << " Sonuc Bulundu  <--" << endl;
    t8 = clock();
    float s7 = t7, s8 = t8;
    cout << "TXT Arama işleminin çalışma süresi " << (s8 - s7) / 1000 << " saniye" << endl;
    cout << "========== TXT Den Cekme Islemi Bitti ==========" << endl;
    cout << "Toplamda : " << sayact << " Kadar Sonuc Bulundu." << endl;


    t10 = clock();
    float s9 = t9, s10 = t10;
    cout<<endl << "Bütün Programın  çalışma süresi " << (s10 - s9) / 1000 << " saniye" << endl;
        return 0;



}