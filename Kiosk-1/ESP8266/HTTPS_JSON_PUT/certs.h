#pragma once

////////////////////////////////////////////////////////////
// certificate chain for locker-api.versicles.com/locker

const char* get_host = "locker-api.versicles.com";
const char* post_host = "locker-iot-api.versicles.com";
const uint16_t port = 443;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Certificate details:
Issued On  Tuesday, 3 January 2023 at 05:30:00
Expires on  Friday, 2 February 2024 at 05:29:59
SHA-256 Fingerprint  AD CC 1E 02 E6 EA 89 AC D9 09 77 F8 8E AF 04 EA D8 C5 A6 36 D6 93 8D 20 EA 07 51 9F ED 89 A7 8F
SHA-1 fingerprint 6A DB 9C 53 29 8A 7C 58 7E BA 59 C4 86 FE 79 32 C6 A2 FC F7
*/

const char fingerprint___versicles_com [] PROGMEM = "6A:DB:9C:53:29:8A:7C:58:7E:BA:59:C4:86:FE:79:32:C6:A2:FC:F7";

/*const char pubkey___versicles_com [] PROGMEM = R"PUBKEY(
-----BEGIN PUBLIC KEY-----

-----END PUBLIC KEY-----
)PUBKEY";
*/

/*
Root Certificate Validity:
Not Before -> 26/05/2015, 05:30:00 GMT+5:30
Not after  -> 17/01/2038, 05:30:00 GMT+5:30
*/
const char cert_Amazon_RSA_2048_M01 [] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)CERT";


// end of certificate chain for api.github.com:443
////////////////////////////////////////////////////////////
