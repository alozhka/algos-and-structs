cd cmake-build-debug

echo "Тест 1"
./lw2 ../tests/correct.pas
echo "Тест 2"
./lw2 ../tests/err_begin_end.pas
echo "Тест 3"
./lw2 ../tests/err_extra_else.pas
echo "Тест 4"
./lw2 ../tests/err_extra_end.pas
echo "Тест 5"
./lw2 ../tests/err_no_then.pas
echo "Тест 6"
./lw2 ../tests/err_record_no_end.pas
echo "Тест 7"
./lw2 ../tests/err_repeat_until.pas

cd ..