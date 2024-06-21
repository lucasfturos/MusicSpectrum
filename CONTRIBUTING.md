# Contribuindo para este Projeto

Agradeço seu interesse em contribuir para este projeto. 

_Ele foi bem divertido de desenvolver e tomara que fique mais divertido ainda com as ideias da comunidade._

## Tutorial de como Contribuir

Após fazer o fork para contribuir com o projeto, siga os seguintes passos antes de começar.

Faça o clone do seu repositório:

```
git clone --recursive https://github.com/<seu usuário do GitHub>/MusicSpectrum.git
```

E defina o upstream:

```
git remote add upstream https://github.com/lucasfturos/MusicSpectrum.git
```

Crie seu branch com o nome do seu usuário:

```
git checkout -b seu_usuario
```

Para manter seu fork atualizado e não afetar sua contruibuição, é necessário reiniciar o número de commits na sua máquina. Faça isso antes de começar a modificar os arquivos, pois perderá seu progresso.

Siga os seguintes passos para atualizar:

```
git remote update
git reset upstream/master --hard
```

Trabalhe normalmente no branch. Quando desejar enviar seu resultado para o seu repositório, faça o push com:

```
git push origin seu_usuario --force
```

Assim seu repositório que foi feito o fork será atualizado.

**Com isso, poderá fazer seu primeiro Pull Request.**

## Pull Request

Ao fazer qualquer modicação do código. Envie um Pull Request com o Título resumido da mudança e dê uma descrição breve sobre as mudanças.

Eu irei aprovar se estiver tudo certo 😉.