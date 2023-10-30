
# Prac_CallCppFromPython

以下のコマンドを順番に実行すると自作Pythonライブラリがビルドされる。

```shell
python -m venv venv
./venv/Scripts/activate
pip install setuptools
python setup.py install
```

Pythonインタープリタを起動して動作確認。

```py
import mysolver
mysolver.calc(2, 3, 4) # =10
```
