# gos

1) Чтобы детектить диагональный градиент надо просто уметь детектить одновременно вертикальный и горизонтальный и пересекать их
2) Воспользуемся идеей из поиска наибольшей нулевой подматрицы (https://e-maxx.ru/algo/maximum_zero_submatrix)
3) Вместо нулевой области у нас градиент, поэтому нужно хранить намного больше инфы + не только горизонтальный стек (как в оригинале) но и вертикальный
4) ???
5) Profit

Таким образом, умеем детектить цветные/черно-белые градиенты, направленные под любым углом.

Асимптотика по времени/памяти - O(размер изображения).


Как запустить:
g++ --std=c++17 main.cpp -O3 -o gradient_finder
mkdir images
python3 reader.py


Результат на тестовых изображениях будет лежать в папке images.

Можно reader.py поправить, попробовать какие-то другие градиенты поискать.
