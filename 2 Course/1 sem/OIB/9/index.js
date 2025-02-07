const algoIdentifier = "AES-CBC";
const button = document.getElementById("rand");
const hash = document.getElementById("hash");
const codeMessage = document.getElementById("codeMessage");
const encode = document.getElementById("encode");
const decode = document.getElementById("decode");
const pack = document.getElementById("pack");
const signa = document.getElementById("signa");

//функция для генерации случайного числа
button.addEventListener("click", () => {
  const array = new Uint8Array(1);
  console.log(crypto.getRandomValues(array)[0]);
});
// Асинхронная функция для вычисления хеша сообщения.
async function digestMessage(message) {
  // Создание нового кодировщика текста.
  const encoder = new TextEncoder();
  // Кодирование сообщения в байты.
  const data = encoder.encode(message);
  // Вычисление хеша с помощью алгоритма SHA-512 и возвращение результата.
  const hash = await crypto.subtle.digest("SHA-512", data);
  return hash;
}
hash.addEventListener("click", () => {
  digestMessage(codeMessage.value).then((digestBuffer) =>
    // Вывод в консоль буфера ArrayBuffer результата хеширования.
    console.log(digestBuffer)
  );
  // Очистка поля ввода.
  codeMessage.value = "";
});
let decryptKey; // Переменная для хранения ключа расшифровки.
let decryptKeyParams = {
  // Параметры для генерации ключа расшифровки.
  name: algoIdentifier,
  length: 256,
};
let byteMessage; // Переменная для хранения зашифрованного сообщения в байтах.
const encryptDecryptParams = {
  // Параметры для операций шифрования/расшифрования.
  name: algoIdentifier,
  // Инициализационный вектор, полученный из случайных значений.
  iv: crypto.getRandomValues(new Uint8Array(16)),
};
async function encodeMessage() {
  // Генерация ключа для шифрования.
  let key = await window.crypto.subtle.generateKey(decryptKeyParams, true, [
    "encrypt",
    "decrypt",
  ]);
  decryptKey = key; // Сохранение ключа для последующей расшифровки.
  // Кодирование исходного текста сообщения в байты.
  const originalPlaintext = new TextEncoder().encode(codeMessage.value);
  // Шифрование сообщения и сохранение результата в byteMessage.
  const ciphertext = await crypto.subtle.encrypt(
    encryptDecryptParams,
    key,
    originalPlaintext
  );
  byteMessage = ciphertext;
  // Вывод зашифрованного сообщения в консоль.
  console.log(ciphertext);
}
encode.addEventListener("click", encodeMessage);
async function decodeMessage() {
  // Расшифровка сообщения и преобразование результата в строку.
  const decryptedPlaintext = await crypto.subtle.decrypt(
    encryptDecryptParams,
    decryptKey,
    byteMessage
  );
  // Вывод расшифрованного текста в консоль.
  console.log(new TextDecoder().decode(decryptedPlaintext));
}
decode.addEventListener("click", decodeMessage);

async function WrapKey() {
  // Параметры для генерации ключа обертывания.
  const keyFormat = "raw";
  const extractable = true;
  const wrappingKeyAlgoIdentifier = "AES-KW";
  const wrappingKeyUsages = ["wrapKey", "unwrapKey"];
  const wrappingKeyParams = {
    name: wrappingKeyAlgoIdentifier,
    length: 256,
  };
  // Генерация ключа обертывания.
  const wrappingKey = await crypto.subtle.generateKey(
    wrappingKeyParams,
    extractable,
    wrappingKeyUsages
  );
  // Вывод ключа обертывания в консоль.
  console.log(wrappingKey);
  // Обертывание ключа расшифровки и вывод результата в консоль.
  const wrappedKey = await crypto.subtle.wrapKey(
    keyFormat,
    decryptKey,
    wrappingKey,
    wrappingKeyAlgoIdentifier
  );
  console.log(wrappedKey);
  // Распаковка ключа и вывод в консоль.
  const unwrappedKey = await crypto.subtle.unwrapKey(
    keyFormat,
    wrappedKey,
    wrappingKey,
    wrappingKeyParams,
    decryptKeyParams,
    extractable,
    ["encrypt", "decrypt"]
  );
  console.log(unwrappedKey);
}
pack.addEventListener("click", WrapKey);
// Функция для создания и проверки цифровой подписи.
let sign = async function () {
  // Параметры для генерации ключевой пары.
  const keyParams = {
    name: "ECDSA",
    namedCurve: "P-256",
  };
  const keyUsages = ["sign", "verify"];
  // Генерация ключевой пары.
  const { publicKey, privateKey } = await crypto.subtle.generateKey(
    keyParams,
    true,
    keyUsages
  );
  // Кодирование сообщения для подписи.
  const message = new TextEncoder().encode("Mes to sign");
  // Параметры для создания и проверки подписи.
  const signParams = {
    name: "ECDSA",
    hash: "SHA-512",
  };
  // Создание подписи.
  const signature = await crypto.subtle.sign(signParams, privateKey, message);
  // Проверка подписи.
  const verified = await crypto.subtle.verify(
    signParams,
    publicKey,
    signature,
    message
  );
  // Вывод параметров подписи, публичного ключа и сообщения в консоль.
  console.log(signParams, publicKey, message);
  // Вывод результата проверки подписи в консоль.
  console.log(verified);
};
// Добавление обработчика события на кнопку 'signa' для события 'click'.
signa.addEventListener("click", () => {
  sign();
});
