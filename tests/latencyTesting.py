import re
import subprocess
import sys

def run_traceroute(command):
    """Runs a traceroute command and returns its output as lines."""
    result = subprocess.run(command, capture_output=True, text=True)
    return result.stdout.splitlines()

def parse_traceroute_output(lines):
    traceroute = []
    hop_pattern = re.compile(r'^\s*(\d+)\s+([\d\.]+)\s+([\d\.]+)ms\s+([\d\.]+)ms\s+([\d\.]+)ms')

    for line in lines:
        match = hop_pattern.match(line)
        if match:
            hop_num = int(match.group(1))
            ip = match.group(2)
            latencies = [float(match.group(i)) for i in range(3, 6)]
            traceroute.append((hop_num, ip, latencies))

    return traceroute

def compare_all_latencies(trace1, trace2, threshold=30.0):
    print(f"{'Hop':<4} {'IP 1':<16} {'IP 2':<16} {'Δ Latencies (ms)':<40} {'Status'}")
    print("-" * 90)

    for hop1, hop2 in zip(trace1, trace2):
        hop_num1, ip1, lats1 = hop1
        hop_num2, ip2, lats2 = hop2

        if hop_num1 != hop_num2:
            print(f"❌ Hop number mismatch: {hop_num1} vs {hop_num2} — skipping")
            continue

        diffs = [abs(a - b) for a, b in zip(lats1, lats2)]
        all_within_threshold = all(diff <= threshold for diff in diffs)
        diff_str = ', '.join(f"{d:.2f}" for d in diffs)

        if ip1 != ip2 and all_within_threshold:
            status = "⚠️  IP mismatch, latency ✅"
        elif all_within_threshold:
            status = "✅"
        else:
            status = "❌"

        print(f"{hop_num1:<4} {ip1:<16} {ip2:<16} {diff_str:<40} {status}")

if __name__ == "__main__":
    # Modify these to your custom traceroute implementations or targets if needed
    cmd1 = ["traceroute", sys.argv[1]]
    cmd2 = ["../ft_traceroute", sys.argv[1]]

    print("Running real traceroute...")
    real_trace_output = run_traceroute(cmd1)

    print("Running ft_traceroute...")
    my_trace_output = run_traceroute(cmd2)

    real_trace = parse_traceroute_output(real_trace_output)
    my_trace = parse_traceroute_output(my_trace_output)

    compare_all_latencies(my_trace, real_trace)
