from pathlib import Path
import pandas as pd
from pandas import ExcelWriter

# Change these
log_dir = "/media/hanskw/UBUNTU 20_0/Scout_Test/2_3_22/log"
rpm_step = 5
use_abs_vals = False

pathlist = Path(log_dir).glob('**/*.csv')
for path in pathlist:
  file_name = str(path)
  if "hs" in file_name:
    out_file = file_name[:-4] + "_output.xlsx"  
    writer = ExcelWriter(out_file)

    print(f"Processing {file_name}, outputting to {out_file}")

    df = pd.read_csv(file_name, names=[
                    "index", "motor_id", "rpm", "current", "pulse"])

    if use_abs_vals:
        df["rpm"] = df["rpm"].abs()
        df["current"] = df["current"].abs()

    df.to_excel(writer, "original")

    for i in range(1, 5):
        out_df = pd.DataFrame(
            columns=["rpm", "avg_current", "max_current", "min_current", "frequency"])
        motor_df = df[df["motor_id"] == i]
        for j, rpm in enumerate(range(motor_df["rpm"].min(), motor_df["rpm"].max(), rpm_step)):
            step_df = motor_df[motor_df["rpm"].between(rpm, rpm+rpm_step)]
            avg_current = step_df["current"].mean()
            min_current = step_df["current"].min()
            max_current = step_df["current"].max()
            frequency = step_df["current"].count()
            out_df.loc[j] = [rpm] + [avg_current] + [max_current] + [min_current] + [frequency]
        out_df = out_df.fillna(0)
        out_df.to_excel(writer, "motor_" + str(i))

    writer.save()
