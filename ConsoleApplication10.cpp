#pragma region Kütüphaneler
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
#pragma endregion

//levenshtein için
#define MIN(x,y) ((x) < (y) ? (x) : (y))
//Karp Rabin içinde gelen Verinin RTF-XML-HTML-TXT den geldiğini anlamıza yarayan değişken
string _gelen;
//Genel Değişkenlerimiz
int i, j  , l1, l2, t, track;
//Verileri dosyalardan çektikten sonra aktardığımız char dizileri
char txt[100000000];
char html[100000000];
char rtf[100000000];
char xml[100000000];
//Char dizlerinin bitişi

//dosya dosya içinde pat kelimesinden kaç tane olduğunu saydığımız sayaç
int sayac = 0;
//Dosyaların içinde toplamda kaç tane pat kelimesinden geçtiğini saydığımız sayaç 
int sayact = 0; 
//MAX değerinin aldığı değer
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
// d Alfabedeki karakter sayısıdır. 
#define d 256  

/* pat -> Aranan Kelime
    txt -> Gelen Char dizisi
    q -> Birincil Numara
*/
void search(char pat[], char txt[], int q , int sayi)
{
   

    int M = strlen(pat);
    int N = strlen(txt);
    int p = 0; // hash value for pattern  
    int t = 0; // hash value for txt  
    int h = 1;

    ofstream dosya("aranan_" + string(pat) + ".txt", ios::out | ios::app);
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;


    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    cout<<endl<<"--------------------------------> " <<"Aranan Kelime : "<< pat << " <-------------------------------" << endl;
    for (i = 0; i <= N - M; i++)
    {
        

        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }
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
 
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;


            if (t < 0)
                t = (t + q);

        }
        if (i == N-M && j != M) {
         

        }

    }
}
#pragma endregion

#pragma region txt
//txt verilerini çekip diziye aktardığımız fonksiyon
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
//html verilerini çekip diziye aktardığımız fonksiyon
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
//rtf verilerini çekip diziye aktardığımız fonksiyon
void rtfcek() {

  
    ifstream myfile("veri.rtf"); 
    if (myfile.is_open()) 
    {
        for (int i = 0; i < 1000000; ++i)
            myfile >> rtf[i];

        myfile.close(); 
    }
    else cout << "Unable to open file";
}
#pragma endregion

#pragma region xml
//xml verilerini çekip diziye aktardığımız fonksiyon
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
 

    //Değişken Tanımlama
    int j = 101; // A prime number  
    int z = 10;
    char pat[256] ;
    int secim;
    setlocale(LC_ALL, "Turkish");
    srand(time(0));
    clock_t t1, t2,t3, t4, t5, t6, t7, t8, t9, t10;
    //Değişken tanımlama bitiş
    //Bütün programın çalışma saatinin başlangıcı
    t9 = clock();

    cout << "Aranacak Kelimeyi Giriniz : ";
    cin.getline(pat,256);
    static char GirilenKelime[MAX];
    char KayitliKelime[MAX];
    //bunu mu demek istediniz ? kısmı için kelimeler
    string kelimler[13] = { "veri", "Data", "DataBase", "oracle", "system", "Program" , "Objects" , "Data Access" , "Data Access" , "Insert" , "update" , "delete" , "table" };

    //Kelimleri büyük küçük halini kontrol ediyor
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
    //xmlcek fonksiyonu çağrılıyor 
    xmlCek();
    //Gelen veriler ile birlikte search fonksiyonuna parametreleri gönderiyoruz
    search(pat, xml, j,1);
    cout<<"--> XML de " << sayac<<" Sonuc Bulundu  <--"<<endl;
    t2 = clock();
    float s1 = t1, s2 = t2;
    cout << "XML Arama işleminin çalışma süresi " << (s2 - s1) / 1000 << " saniye" << endl;
    cout << "========== XML Den Cekme Islemi Bitti ==========" << endl << endl;


    t3 = clock();
    sayac = 0;
    cout << " ========== RTF den Cekme Islemi Basliyor ========== " << endl;
    //rtfcek fonksiyonu çağrılıyor 
    rtfcek();
    //Gelen veriler ile birlikte search fonksiyonuna parametreleri gönderiyoruz
    search(pat, rtf, j,2);
    cout << "--> RTF de " << sayac << " Sonuc Bulundu  <--" << endl;
    t4 = clock();
    float s3 = t3, s4 = t4;
    cout << "RTF Arama işleminin çalışma süresi " << (s4 - s3) / 1000 << " saniye" << endl;
    cout << "========== RTF Den Cekme Islemi Bitti ==========" << endl << endl;


    t5 = clock();
    sayac = 0;
    cout << " ========== Html den Cekme Islemi Basliyor ========== " << endl;
    //htmlcek fonksiyonu çağrılıyor 
    htmlcek();
    //Gelen veriler ile birlikte search fonksiyonuna parametreleri gönderiyoruz
    search(pat, html, j,3);
    cout << "--> Html de " << sayac << " Sonuc Bulundu  <--" << endl;
    t6 = clock();
    float s5 = t5, s6 = t6;
    cout << "Html Arama işleminin çalışma süresi " << (s6 - s5) / 1000 << " saniye" << endl;
    cout << "========== Html Den Cekme Islemi Bitti =========="<<endl << endl;


    t7 = clock();
    sayac = 0;
    cout << " ========== TXT den Cekme Islemi Basliyor ========== " << endl;
    //veriCekTxt fonksiyonu çağrılıyor 
    veriCekTxt();
    //Gelen veriler ile birlikte search fonksiyonuna parametreleri gönderiyoruz
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