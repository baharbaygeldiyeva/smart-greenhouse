import processing.serial.*;

Serial port;
boolean sulamaDurumu = false;

void setup() {
  size(200, 200);
  String portAdi = Serial.list()[0]; // Arduino'nun bağlı olduğu portu seçin
  port = new Serial(this, portAdi, 9600);
  port.bufferUntil('\n');
}

void draw() {
  background(255);
  
  // Sulama durumunu görselleştir
  if (sulamaDurumu) {
    fill(0, 255, 0); // Yeşil renk
  } else {
    fill(255, 0, 0); // Kırmızı renk
  }
  ellipse(width/2, height/2, 100, 100);
}

void mouseClicked() {
  // Mouse tıklamasıyla sulama durumunu değiştir
  sulamaDurumu = !sulamaDurumu;
  
  // Arduino'ya komut gönder
  if (sulamaDurumu) {
    port.write('S');
  } else {
    port.write('F');
  }
}

void serialEvent(Serial port) {
  // Arduino'dan veri geldiğinde
  String veri = port.readStringUntil('\n');
  if (veri != null) {
    veri = veri.trim();
    // Arduino'dan gelen sıcaklık verisini al
    int sicaklik = Integer.parseInt(veri);
    println("Sıcaklık: " + sicaklik + "°C");
  }
}
