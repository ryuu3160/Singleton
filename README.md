# Singleton

CRTPとmozc式シングルトンを組み合わせた、安全で使いやすいシングルトン量産システムです。

## 概要

このシングルトン実装は、**CRTP（Curiously Recurring Template Pattern）** と **mozc式シングルトン** の長所を組み合わせた、C++向けのヘッダオンリーライブラリです。

テンプレートベースのアプローチにより、型安全性を保ちながら、シンプルで直感的なシングルトン実装が可能になります。

## 使い方

### 基本的な使用方法

シングルトンにしたいクラスを以下のように定義するだけです：

```cpp
class MyClass : public Singleton<MyClass>
{
    friend class Singleton<MyClass>;
    
    // private コンストラクタなど必要な実装
private:
    MyClass() = default;
};
```

**重要なポイント：**
- `Singleton<MyClass>` を継承する
- `Singleton<MyClass>` をフレンドクラスに設定する

これだけで、`MyClass` はシングルトンとして機能します。

### インスタンスの取得

```cpp
MyClass& instance = MyClass::GetInstance();
```

### インスタンスの解放

プログラム終了時に、以下のコードを実行してください：

```cpp
SingletonController::Release();
```

このメソッドを呼び出すと、**すべてのシングルトンオブジェクトが生成とは逆順で安全に解放されます。**

これにより、複数のシングルトン間の依存関係がある場合でも、正しい順序でクリーンアップが行われます。

## 特徴

✅ **型安全** — テンプレートにより、コンパイル時に型チェックが行われます  
✅ **ヘッダオンリー** — ヘッダファイルをインクルードするだけで使えます  
✅ **シンプル** — 複雑なボイラープレートコードが不要です  
✅ **安全な破棄** — シングルトン間の依存関係を自動的に管理します  
✅ **CRTP + mozc式** — 両者の長所を兼ね備えています  

## 使用例

```cpp
#include "singleton.hpp"

// ロギングシステム
class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;
    
private:
    Logger() = default;
    
public:
    void Log(const std::string& message)
    {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// 設定管理
class Config : public Singleton<Config>
{
    friend class Singleton<Config>;
    
private:
    Config() = default;
    
public:
    void LoadConfig()
    {
        // 設定ロード処理
    }
};

int main()
{
    // シングルトンの使用
    Logger::GetInstance().Log("Application started");
    Config::GetInstance().LoadConfig();
    
    // ... アプリケーション処理 ...
    
    // プログラム終了時にすべてのシングルトンを解放
    SingletonController::Release();
    
    return 0;
}
```

## ライセンス

このプロジェクトは **MIT License** の下で公開されています。  
詳しくは [LICENSE](LICENSE) ファイルをご覧ください。

## 注意事項

- シングルトンの破棄順序を確実にするため、プログラム終了時には必ず `SingletonController::Release()` を呼び出してください
- マルチスレッド環境での使用を想定している場合は、スレッドセーフティを別途確保してください

---

何か質問や改善案があれば、気軽に声をかけてね～！
