## Private encryption interface access document

### Use a private encryption scheme
Before enterring the room, call the enablePayloadPrivateEncryption method to enable private encryption, please refer to the following steps to generate and set the key and salt respectively. 

- 1.All users in the same room must use the same encryption algorithm, key and salt.
- 2.After the user exits the room, the SDK will automatically close the private encryption. To turn private encryption back on, you need to call this method before the user enters the room again.

### Generate and set keys
On your server, refer to the following command to randomly generate a String-type key through OpenSSL.

```
// Randomly generate a string type, 16-byte key, and pass the key to the encryptionKey parameter of enablePayloadPrivateEncryption.
openssl rand -hex 16
a2e898d07a304246044f899a16123263
```

### Generate and set the salt
On your server, refer to the following command to randomly generate a Base64-encoded, 32-byte salt via OpenSSL.

```
// Randomly generate a Base64-encoded, 32-byte salt, and pass the salt to the encryptionSalt parameter of TRTCPayloadPrivateEncryptionConfig.
openssl rand -base64 32
3ZZ0nV/rDVUzTa6tXyz+F7rrUYIcxRqX5fiUto/FbZA=
```

### Sample code
```
int ifSuccess = mTRTCCloud.enablePayloadPrivateEncryption(true, "1111222233334444", "11112222333344445555666677778888");
```