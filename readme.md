<p align="center"><a href="https://nandateknik.my.id" target="_blank"><img src="https://blogger.googleusercontent.com/img/a/AVvXsEjwJW1smTUSgRIsdJLF7v4Pbwu3TwFTdFwpRkWTLcdu-esrY-MbY54D8YC5I-IPGiKzb5war06-wlcRr2HAfhId2_mHeQXUDc-B046j4tRZAv04Z-DcbxaVmEwNu9uBeG81M1zQO63du49VSIx2RzPjWtqB8eWYU5jH1F5tT8eJ6ZMOzpcEtcWw5ycz=s548" width="400"></a></p>

<p align="center">
<a href="#"><img src="https://img.shields.io/badge/BETA-V.0.1-%3CCOLOR%3E.svg"></a>
<a href="#"><img src="https://img.shields.io/badge/BY-NANDADEV-blue"></a>
</p>

# NODEMCU ESP8266 ARDUINO


Sebuah project yang dikerjakan untuk kebutuhan iot di lingkungan Dinas Kominfo dan Persandian Kabupaten Banyuwangi.

### Fitur Aplikasi :
- **HTTP POST JSON** Digunakan untuk melakukan post JSON dari web untuk cek kondisi lampu ON atau OFF
- **HTTP GET JSON** Kontroling lampu dari kondisi di Dashboard API IOT

### Pin Reference Nodemcu :
Untuk penggunaan pembacaan pin Cek tabel berikut ini :

| Nama         | Pin Output | Pin Input  |
| -----------  |:--:|:--:|
| LAMPU 1      | D0 | D1 |
| LAMPU 2      | D3 | D2 |
| LAMPU 3      | D4 | D6 |
| LAMPU 3      | D5 | D7 |

- **Pin Output** Digunakan untuk menggerakan beban seperti relay yang dihubungkan dengan beban.
- **Pin Input** Digunakan untuk Membaca status realtime dari 2 saklar yang berbeda.
  
Pemasangan tidak boleh terbalik agar status realtime tidak salah

### Libraries :
- **Arduino JSON** [Docs](https://arduinojson.org/v6/doc/)

## API Collect HTTP GET JSON
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

## API Collect HTTP POST JSON
```Json
{
  "data":[{
    "pin" : "pin input",
    "kondisi " : 1,
    }]
}
```




