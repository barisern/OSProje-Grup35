
# İşletim Sistemleri Proje Ödevi

### Üyelerin Adları

- Ömer Barış Eren - B191210085
- Abdurrahman Kemal Bulun - B191210091
- Zidan Omar Hamid - B181210568

### Dosyalar, dizinler ve açıklamaları

| Dizin |  Açıklama |
| :------------ | :----- |
| /bin    | Derlenmiş çalıştırılabilir dosyaları içeren klasördür. |
| /src   | Kaynak kodu dosyalarını içeren klasördür.        | 
| /include | Başlık dosyalarını içeren klasördür.        | 

| Dosya |  Açıklama |
| :------------ | :----- |
| main.c     |  Programın kaynak kodlarını içerir, programın başlama noktasıdır. |
| main.h    |  main.c için oluşturulmuş başlık dosyası.  | 
| makefile | Programın derlenmesi için kodları içerir.  | 

### Programın Derlenmesi

```bash
make
```

veya

```bash
gcc ./src/main.c -o ./bin/main
```

### Programın çalıştırma talimatları

- Derleme sonrası /bin klasöründe oluşan ./main dosya çalıştırılıp program başlatılabilir, veya `make` komutu kullanıp derlenip çalıştırılabilir.

### Geliştirme sırasında karşılaştığınız zorluklar

- showpid komutu

### Kaynaklar

- https://linux.die.net/man/
- https://stackoverflow.com/