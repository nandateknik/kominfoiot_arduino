<p align="center"><a href="https://nandateknik.my.id" target="_blank"><img src="https://blogger.googleusercontent.com/img/a/AVvXsEjwJW1smTUSgRIsdJLF7v4Pbwu3TwFTdFwpRkWTLcdu-esrY-MbY54D8YC5I-IPGiKzb5war06-wlcRr2HAfhId2_mHeQXUDc-B046j4tRZAv04Z-DcbxaVmEwNu9uBeG81M1zQO63du49VSIx2RzPjWtqB8eWYU5jH1F5tT8eJ6ZMOzpcEtcWw5ycz=s548" width="400"></a></p>

<p align="center">
<a href="#"><img src="https://img.shields.io/badge/PRODUCTION-V.2-%3CCOLOR%3E.svg"></a>
<a href="#"><img src="https://img.shields.io/badge/BY-NANDADEV-blue"></a>
</p>


# NODEMCU ESP8266 ARDUINO


Sebuah project yang dikerjakan untuk kebutuhan iot di lingkungan Dinas Kominfo dan Persandian Kabupaten Banyuwangi.

### Fitur Aplikasi :
- **kONTROL LAMPU** Digunakan untuk controller lampu.
- **KONTROL AC** Digunakan untuk controller AC.
- **KONTROL SENSOR** Digunakan untuk controller SENSOR.

### Libraries :
- **Arduino JSON** [Docs](https://arduinojson.org/v6/doc/)

### Pin Reference Nodemcu :

![alt text](https://github.com/nandateknik/kominfoiot_arduino/blob/master/img/nodemcu.webp?raw=true)


# KONFIGURASI NODEMCU ESP82266 CODE
Berikut ini adalah cara konfigurasi nodemcu esp8266 code untuk koneksi ke wifi.

```Ino
const char* wifiName = "KOMINFO";
const char* wifiPass = "banyuwangiku";
String host = "http://backend.banyuwangikab.go.id/public/api/lampu/";
String group = "A";
```

### Penjelasan Code :
- **wifiName :** SSID wifi yang akan digunakan untuk koneksi ke internet.
- **wifiPass :** Password wifi yang akan digunakan untuk koneksi ke internet.
- **host :** url api untuk dashboard.
- **group :** No Unik tiap-tiap hardware.


### Cara instalasi AC Controller
![alt text](https://github.com/nandateknik/kominfoiot_arduino/blob/master/img/accontroller.png?raw=true)
- NodeMCU pin D5 dan D6 dihubungkan dengan relay 5volt
- out dari relay 5volt dihubungkan ke tombol on off module pada ac
- Untuk relay status menggunakan relay 220 volt kemudian pin NO dihubungkan ke pin D7

### Cara Instalasi Lampu Controller
Sebelum melakukan instalasi hardware, ada beberapa yang harus diperhatikan. Untuk penggunaan pembacaan pin Cek tabel berikut ini :

| Nama         | Pin Output | Pin Input  |
| -----------  |:--:|:--:|
| LAMPU 1      | D0 | D1 |
| LAMPU 2      | D3 | D2 |
| LAMPU 3      | D4 | D6 |
| LAMPU 4      | D5 | D7 |

- **Pin Output** Digunakan untuk menyalakan beban seperti relay yang dihubungkan dengan beban.
- **Pin Input** Digunakan untuk Membaca status realtime dari 2 saklar yang berbeda.

![alt text](https://github.com/nandateknik/kominfoiot_arduino/blob/master/img/lampucontroller.png?raw=true)
Pemasangan tidak boleh terbalik agar status realtime tidak salah Contoh :
- Output D0 digunakan untuk menyalakan ruangan kabid, untuk pembacaan status realtime dari D0 adalaha pin D1
- untuk pembacaan realtime bisa menggunakan ssr pada arduino.

### Controller sensor
Berikut ini penggunaan controller sensor pada nodemcu.

| Nama         | Pin Input  |
| -----------  |:--:|
| SENSOR 1      | D1 |
| SENSOR 2      | D2 |
| SENSOR 3      | D5 |
| SENSOR 4      | D6 |
| SENSOR 5      | D7 |

penggunaan controler sensor bisa menggunakan salah satu pin nodemcu. untuk integrasi tinggal menyesuaikan serial number dan pin yang digunakan contohnya kita menggunakan pin D2 jadi api collectnya :

## API Collect HTTP POST JSON SENSOR
```Json
{
  "data":[{
    "pin" : "pin input",
    "kondisi " : 1,
    }]
}
```

Didatabase di setting pin, group dan kondisi.

## API Collect HTTP GET JSON CONTROLLER LAMPU
```Json
{
  "data": [
    {
      "pin": 16,
      "grup": "A",
      "status": "1",
      "kondisi": "1",
      "created_at": "2023-06-12T13:30:34.000000Z",
      "updated_at": "2023-08-13T11:59:05.000000Z",
      "updated_by": 1
    },
    {
      "id": 1,
      "name": "R. Kabid",
      "pin": 16,
      "grup": "A",
      "status": "1",
      "kondisi": "1",
      "created_at": "2023-06-12T13:30:34.000000Z",
      "updated_at": "2023-08-13T11:59:05.000000Z",
      "updated_by": 1
    },{
      "id": 1,
      "name": "R. Kabid",
      "pin": 16,
      "grup": "A",
      "status": "1",
      "kondisi": "1",
      "created_at": "2023-06-12T13:30:34.000000Z",
      "updated_at": "2023-08-13T11:59:05.000000Z",
      "updated_by": 1
    },{
      "id": 1,
      "name": "R. Kabid",
      "pin": 16,
      "grup": "A",
      "status": "1",
      "kondisi": "1",
      "created_at": "2023-06-12T13:30:34.000000Z",
      "updated_at": "2023-08-13T11:59:05.000000Z",
      "updated_by": 1
    }]
    }
```

## API Collect HTTP POST JSON CONTROLLER LAMPU
```Json
{
  "data":[{
    "pin" : "PIN_D2",
    "kondisi " : 1,
    }]
}
```


## API Collect HTTP GET JSON CONTROLLER AC
```Json
{
  "data":{
    "kondisi " : 1,
    }
}
```
## API Collect HTTP POST JSON CONTROLLER AC
```Json
{
  "data":{
    "status " : 1,
    }
}
```




