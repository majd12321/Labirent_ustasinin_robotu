//Ultrasonik Mesafe Sensörlerin tanımtımı
const int trig_sag = 2;
const int echo_sag = 3;
int mesafe_sag;
int sure_sag;
const int trig_on = 4;
const int echo_on = 5;
int mesafe_on;
int sure_on;
const int trig_sol = 6;
const int echo_sol = 7;
int mesafe_sol;
int sure_sol;
const int trig_arka = A2;
const int echo_arka = A3;
int mesafe_arka;
int sure_arka;

int yol_ortasi;



//motorların ve hızları tanıtımı
int sag_mtr_ileri = 8;
int sag_mtr_geri = 9;
int sag_mtr_hizi = 10;
int sag_hiz = 150;
int sol_mtr_ileri = 12;
int sol_mtr_geri = 13;
int sol_mtr_hizi = 11;
int sol_hiz = 150;


//lm35 sıcaklık sansörünün gereken değişkenler
// Amacı: Ultrasonik Mesafe Sensörlerin değerleri daha net çıkartmak içindir.
int lm35 = A0;
int okunan_deger;
float sicaklik;
float dalga_hizi;

// zeminin rengi ne renk olduğu bilinmek için
int TCRT5000 = A1;
//*****************************************

//robotun koordinatlarını değiştirmek için 
bool yon = true;

void setup() {
  Serial.begin(9600);
//Burada pinleri tanımlanır
  pinMode(sag_mtr_ileri, OUTPUT);
  pinMode(sag_mtr_geri, OUTPUT);
  pinMode(sag_mtr_hizi, OUTPUT);
  pinMode(sol_mtr_ileri, OUTPUT);
  pinMode(sol_mtr_geri, OUTPUT);
  pinMode(sol_mtr_hizi, OUTPUT);
  pinMode(trig_sag, OUTPUT);
  pinMode(echo_sag, INPUT);
  pinMode(trig_on, OUTPUT);
  pinMode(echo_on, INPUT);
  pinMode(trig_sol, OUTPUT);
  pinMode(echo_sol, INPUT);
  pinMode(trig_arka, OUTPUT);
  pinMode(echo_arka, INPUT);
  pinMode(TCRT5000, INPUT);
  
  //*****************************************

//burada dalga hızını değeri hesaplanır 
  okunan_deger = analogRead(lm35);
  sicaklik = (5000.0 / 1023.0) * okunan_deger;
  sicaklik = sicaklik / 10.0;
  dalga_hizi = 1 + (sicaklik / 273);
  dalga_hizi = sqrt(dalga_hizi);
  dalga_hizi = dalga_hizi * 33100;
  dalga_hizi = dalga_hizi / 1000000;
  dalga_hizi = 1 / dalga_hizi;


}



void loop() {
  int taban_rengi = analogRead(TCRT5000);
  if (taban_rengi >= 900)
  {

    if (yon == true) {

      sag_mesafe();
      on_mesafe();
      sol_mesafe();
      arka_mesafe();



      while (mesaf_sol <= 5 and mesafe_on >= 10  and mesafe_sag <= 5) {
        sag_mesafe();
        on_mesafe();
        sol_mesafe();
        arka_mesafe();
        // robot dumduz ilerletir
        yol_ortasi = (mesafe_sag + mesafe_sol) / 2;
        while (mesafe_sag < yol_ortası) {
          sag_hiz = sag_hiz + 30;
          duz_ileri_gitme();
        }
        while (mesafe_sol < yol_ortası) {
          sol_hiz = sol_hiz + 30;
          duz_ileri_gitme();
        }
        while (mesafe_sag == yol_ortası) {

          duz_ileri_gitme();
        }

      }


      if (mesaf_sol <= 5 and mesafe_on >= 10 or mesafe_on <= 5 and mesafe_sag >= 10)
      {
        duz_saga_donme();
      }
      else if (mesaf_sol >= 10 and mesafe_on <= 5  and mesafe_sag >= 10)
      {
        duz_saga_donme();
      }
      else if (mesaf_sol >= 10 and mesafe_on <= 5  and mesafe_sag <= 5)
      {
        duz_sola_donme();
      }
      else if (mesaf_sol <= 5 and mesafe_on <= 5  and mesafe_sag <= 5)
      {
        yon = false ;
      }


    }
    //*****************************************//*****************************************//

    else if (yon == false) {
      sag_mesafe();
      on_mesafe();
      sol_mesafe();
      arka_mesafe();

      while (mesaf_sol <= 5 and mesafe_arka >= 10  and mesafe_sag <= 5) {

        sag_mesafe();
        on_mesafe();
        sol_mesafe();
        arka_mesafe();
        yol_ortasi = (mesafe_sag + mesafe_sol) / 2;

        while (mesafe_sag < yol_ortası) {
          sag_hiz = sag_hiz + 30;
          arka_ileri_gitme();
        }
        while (mesafe_sol < yol_ortası) {
          sol_hiz = sol_hiz + 30;
          arka_ileri_gitme();
        }
        while (mesafe_sag == yol_ortası) {

          arka_ileri_gitme();
        }
      }


      if (mesaf_sol >= 10 and mesafe_arka >= 10 or mesafe_arka <= 5 and mesafe_sag <= 5)
      {
        arka_saga_donme();
      }
      else if (mesaf_sol >= 10 and mesafe_arka <= 5  and mesafe_sag >= 10)
      {
        arka_saga_donme();
      }
      else if (mesaf_sol <= 5 and mesafe_arka <= 5  and mesafe_sag >= 10)
      {
        arka_sola_donme();
      }
      else if (mesaf_sol <= 5 and mesafe_arka <= 5  and mesafe_sag <= 5)
      {
        yon = true ;
      }

    }

  }
  
  else {
    bitis_nokta_vardin();
  }

}



//****************************************************************************

void bitis_nokta_vardin() {
  digitalWrite(sag_mtr_ileri, 0);
  digitalWrite(sag_mtr_geri, 0);
  analogWrite(sag_mtr_hizi, 0);
  digitalWrite(sol_mtr_ileri, 0);
  digitalWrite(sol_mtr_geri, 0);
  analogWrite(sol_mtr_hizi, 0);
}

void sag_mesafe() {
  digitalWrite(trig_sag, 0);
  delayMicroseconds(2);
  digitalWrite(trig_sag, 1);
  delayMicroseconds(10);
  digitalWrite(trig_sag, 0);
  sure_sag = pulseIn(echo_sag, 1);
  mesafe_sag = (sure_sag / 2) / dalga_hizi ;
  Serial.print("sağ mesafe = ");
  Serial.print(sag_mesafe);
}


void on_mesafe() {
  digitalWrite(trig_on, 0);
  delayMicroseconds(2);
  digitalWrite(trig_on, 1);
  delayMicroseconds(10);
  digitalWrite(trig_on, 0);
  sure_on = pulseIn(echo_on, 1);
  mesafe_on = (sure_on / 2) / dalga_hizi ;
  Serial.print("on mesafe = ");
  Serial.print(on_mesafe);
}

void sol_mesafe() {
  digitalWrite(trig_sol, 0);
  delayMicroseconds(2);
  digitalWrite(trig_sol, 1);
  delayMicroseconds(10);
  digitalWrite(trig_sol, 0);
  sure_sol = pulseIn(echo_sol, 1);
  mesafe_sol = (sure_sol / 2) / dalga_hizi ;
  Serial.print("sol mesafe = ");
  Serial.print(sol_mesafe);
}

void arka_mesafe() {
  digitalWrite(trig_aka, 0);
  delayMicroseconds(2);
  digitalWrite(trig_arka, 1);
  delayMicroseconds(10);
  digitalWrite(trig_arka, 0);
  sure_arka = pulseIn(echo_arka, 1);
  mesafe_arka = (sure_arka / 2) / dalga_hizi ;
  Serial.print("arka mesafe = ");
  Serial.print(arka_mesafe);
}



void duz_ileri_gitme() {
  digitalWrite(sag_mtr_ileri, 1);
  digitalWrite(sag_mtr_geri, 0);
  analogWrite(sag_mtr_hizi, sag_hiz);
  digitalWrite(sol_mtr_ileri, 1);
  digitalWrite(sol_mtr_geri, 0);
  analogWrite(sol_mtr_hizi, sol_hiz);
}

void duz_saga_donme() {
  digitalWrite(sag_mtr_ileri, 1);
  digitalWrite(sag_mtr_geri, 0);
  analogWrite(sag_mtr_hizi, 50);
  digitalWrite(sol_mtr_ileri, 1);
  digitalWrite(sol_mtr_geri, 0);
  analogWrite(sol_mtr_hizi, 100);
}

void duz_sola_donme() {
  digitalWrite(sag_mtr_ileri, 1);
  digitalWrite(sag_mtr_geri, 0);
  analogWrite(sag_mtr_hizi, 100);
  digitalWrite(sol_mtr_ileri, 1);
  digitalWrite(sol_mtr_geri, 0);
  analogWrite(sol_mtr_hizi, 50);
}

void arka_gitme() {
  digitalWrite(sag_mtr_ileri, 0);
  digitalWrite(sag_mtr_geri, 1);
  analogWrite(sag_mtr_hizi, sag_hiz);
  digitalWrite(sol_mtr_ileri, 0);
  digitalWrite(sol_mtr_geri, 1);
  analogWrite(sol_mtr_hizi, sol_hiz);
}

void arka_saga_donme() {
  digitalWrite(sag_mtr_ileri, 0);
  digitalWrite(sag_mtr_geri, 1);
  analogWrite(sag_mtr_hizi, 100);
  digitalWrite(sol_mtr_ileri, 0);
  digitalWrite(sol_mtr_geri, 1);
  analogWrite(sol_mtr_hizi, 50);
}

void arka_sola_donme() {
  digitalWrite(sag_mtr_ileri, 0);
  digitalWrite(sag_mtr_geri, 1);
  analogWrite(sag_mtr_hizi, 50);
  digitalWrite(sol_mtr_ileri, 0);
  digitalWrite(sol_mtr_geri, 1);
  analogWrite(sol_mtr_hizi, 100);
}
