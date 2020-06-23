# corewar
## Задание для Алины.

Написать 16 операций, которые может исполнять виртуальная машина. Очень важно, чтобы эти 16 функций как-то адекватно хранились и к любой можно было удобно обратиться. Желательно чтобы я сразу поняла как их вызывать, или с минимальными пояснениями.
Не забыть такие вещи, как: непостоянный размер аргумента типа t_dir (2 или 4 байта), подсчет сколько байтов нужно будет перепрыгнуть для перехода к следующей операции и записи этого в каретку.
Файл arena.c (пока что, потом может перенесем) будет содержит некоторые функции работы с памятью арены, в т.ч. обрезку по модулю длины общей памяти арены, чтение и запись чисел в big-endian (пока можешь считать, что я эти функции сделаю, пока заглушки висят). 

Наиболее полное описание операций здесь https://github.com/VBrazhnik/Corewar/wiki/Ассемблер но надо аккуратно, возможно в сабджекте есть что-то еще.
