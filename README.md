# wordle-json
- В этом проекте находятся JSONSchem'ы проекта wordle.
- Тесты для сгенерированных файлов.

## Сгенерировать файлы
```bash
git clone https://github.com/alec-chicherini/wordle-json.git
cd wordle-json
docker build --target=wordle_json_build . -t wordle-json-build
cd ~
```

## Запустить тесты
```bash
docker run --rm --privileged wordle-json-build
```