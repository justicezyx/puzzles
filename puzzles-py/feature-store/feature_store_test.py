import pytest
from datetime import datetime, timedelta

from feature_store import write, read, db


def clean_db():
  keys = db.keys()
  for k in keys:
    del db[k]


@pytest.fixture(autouse=True)
def cleaup_before_tests():
  clean_db()
  # run test
  yield


def test_write_read():
  id = "A"
  features = {
    "feature_1": 1,
    "feature_2": [1, 2, 3],
  }
  write(id, **features)
  result = read(id)
  assert result.keys() == features.keys()
  assert result.items() == features.items()


def test_read_not_found():
  id = "test"
  try:
    result = read(id)
    assert False, f"read should raise on missing key, but returned {result}"
  except LookupError:
    assert True
  except Exception as e:
    assert False, f"unexpected exception type rasied: {e}"


# ------------------------------------
# UNCOMMENT EVERYTHING BELOW THIS LINE
# ------------------------------------


def test_read_write_at_timestamp():
  id = "A"
  features_now = {
    "feature_1": 1,
  }
  features_before = {
    "feature_1": 2,
  }
  now = datetime.now()
  print("now:", now.timestamp())
  before = now - timedelta(days=1)

  write(id, timestamp=now, **features_now)
  write(id, timestamp=before, **features_before)

  result = read(id, timestamp=now)
  assert result.keys() == features_now.keys()
  assert result.items() == features_now.items()


def test_read_write_before_timestamp():
  id = "A"
  features_now = {
    "feature_1": 1,
  }
  features_before = {
    "feature_1": 2,
  }
  now = datetime.now()
  before = now - timedelta(days=1)
  between = now - timedelta(hours=12)

  write(id, timestamp=now, **features_now)
  write(id, timestamp=before, **features_before)

  result = read(id, timestamp=between)
  assert result.keys() == features_before.keys()
  assert result.items() == features_before.items()


def test_read_at_timestamp_not_found():
  id = "A"
  features = {
    "feature_1": 1,
    "feature_2": [1, 2, 3],
  }
  now = datetime.now()
  write(id, timestamp=now, **features)

  before = now - timedelta(days=1)

  try:
    result = read(id, before)
    assert False, f"read should raise when there is no previous key that exists, but returned {result}"
  except LookupError:
    assert True
  except Exception as e:
    assert False, f"unexpected exception type rasied: {e}"


def test_out_of_order_writes():
  id = "A"

  now = datetime.now()
  features_now = {"feature": 1}

  earliest = now - timedelta(days=1)
  features_earliest = {"feature": 2}

  earlier = now - timedelta(hours=1)
  features_earlier = {"feature": 3}

  future = now + timedelta(days=1)
  features_future = {"feature": 4}

  write(id, **features_now)
  write(id, timestamp=earliest, **features_earliest)
  write(id, timestamp=earlier, **features_earlier)
  write(id, timestamp=future, **features_future)

  result = read(id)
  print("result:", result, "features_now:", features_now)
  assert result.keys() == features_now.keys()
  assert result.items() == features_now.items()

