#include <iostream>
#include <vector>

template<class T>
class Table;

template<class T>
class Row
{
  friend class Table<T>;
public:
  explicit Row(const size_t number)
  : row(number)
  {
    //row = new T[number];
  }

  const T& operator [] (const size_t i) const {
    return row[i];
  }

  T& operator [] (const size_t i) {
    return row[i];
  }

protected:
  std::vector<T> row;
};

template<class T>
class Table
{
public:
  Table() = delete;
  explicit Table(const size_t rows, const size_t columns)
  : m_rows(rows, Row<T>(columns))
  {}

  const Row<T>& operator[] (const size_t row) const {
    return m_rows[row];
  }

  Row<T>& operator[] (const size_t row) {
    return m_rows[row];
  }

  void Resize(const size_t rows, const size_t columns) {
    m_rows.resize(rows, Row<T>(columns));
    for(auto& r: m_rows) {
      r.row.resize(columns);
    }
  }

  std::pair<size_t, size_t> Size(void) {
    size_t r = m_rows.size();
    size_t c = 0;
    if (r > 0) {
      c = m_rows[0].row.size();
    }

    return {r, c};
  }

private:
  std::vector<Row<T>> m_rows;
};

using namespace std;

int main()
{
  cout << "Hello Table" << endl;

  Table<int> t(10, 4);

  t[2][2] = 4;

  cout << t[2][2] << endl;
  cout << t[2][3] << endl;

  cout << "Size: " << t.Size().first << " " << t.Size().second << endl;

  t.Resize(5, 5);

  cout << t[2][2] << endl;

  cout << "Size: " << t.Size().first << " " << t.Size().second << endl;

  return 0;
}
