from datetime import datetime
from typing import Dict, Any

db = {}

def find_newest_at_or_before(id: str, ts_limit: datetime) -> Dict[str, Any]:
  newest_ts = None
  res = None
  for ts, feature in db[id].items():
    if float(ts) <= ts_limit.timestamp():
      if newest_ts is None or float(ts) > newest_ts:
        newest_ts = float(ts)
        res = feature
  return res


def read(id: str, timestamp: datetime = None) -> Dict[str, Any]:
  if id not in db:
    raise LookupError("id not found")

  if timestamp is None:
    timestamp = datetime.now()

  res = find_newest_at_or_before(id, timestamp)
  if res is None:
    raise LookupError("no data found")
  return res


def write(id: str,
          timestamp: datetime = None,
          **features: Dict[str, Any]) -> None:

  if timestamp is None:
    timestamp = datetime.now()
  print("id:", id, "timestamp:", timestamp.timestamp())
  if id not in db:
    db[id] = {timestamp.timestamp(): features}
    return
  db[id][timestamp.timestamp()] = features
