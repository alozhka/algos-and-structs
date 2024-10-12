cd cmake-build-debug

echo "Тест 1. Ожидается без ошибок"
./lw2 ../tests/correct.pas
echo "Тест 2. Ожидается без ошибок"
./lw2 ../tests/correct_no_else.pas
echo "Тест 3. Ожидается 8 строка"
./lw2 ../tests/err_begin_end.pas
echo "Тест 4. Ожидается 8 строка"
./lw2 ../tests/err_extra_else.pas
echo "Тест 5. Ожидается 6 строка"
./lw2 ../tests/err_extra_end.pas
echo "Тест 6. Ожидается 5 строка"
./lw2 ../tests/err_no_then.pas
echo "Тест 7. Ожидается 7 строка"
./lw2 ../tests/err_record_no_end.pas
echo "Тест 8. Ожидается 6 строка"
./lw2 ../tests/err_repeat_until.pas

cd ..