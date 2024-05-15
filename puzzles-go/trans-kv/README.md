# Key Value Store with Transactions Support (similar to FoundationDB)

* Initialization
  ```
  store = new Store(<anything>)
  ```
* Data Manipulation
  ```
  store.put(K, V) store.get(K) store.delete(K)
  ```
* Transactions
  ```
  store.begin()
  store.commit()
  store.rollback()
  ```

Example
```
store.begin()
store.put(“a”, 50)
store.begin()
store.put(“a”, 60)
store.rollback()
store.commit()
expect store.get(“a”) == 50
```
