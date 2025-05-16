# ft_traceroute

A custom implementation of the traceroute utility in C. This project tracks the route that packets take to reach a network host.

## Features

- Traces the path packets take to a network host
- Supports UDP probes
- Configurable number of probes per hop
- Adjustable maximum TTL
- Configurable wait time for responses
- Debug mode for detailed output

## Prerequisites

- GCC compiler
- Make
- Root privileges (for raw socket operations)

## Installation

```bash
git clone https://github.com/UBA-code/ft_traceroute.git
cd ft_traceroute
make
```

## Usage

```
sudo ./ft_traceroute [options] host

Options:
  -d            Enable debug output
  -f first_ttl  Set initial TTL (default: 1)
  -m max_ttl    Set maximum number of hops (default: 30)
  -p port       Set starting port (default: 33434)
  -q nqueries   Set number of probes per hop (default: 3)
  -w waittime   Set timeout for responses in seconds (default: 5)
```

## Examples

Basic usage:

```bash
sudo ./ft_traceroute google.com
```

With custom options:

```bash
sudo ./ft_traceroute -m 20 -q 4 -w 3 google.com
```

## Output Format

For each hop, the output shows:

- Hop number
- IP address of the router/host
- Response time in milliseconds for each probe

Example output:

```
 1  192.168.1.1  0.123ms  0.156ms  0.189ms
 2  10.0.0.1     1.234ms  1.567ms  1.890ms
 3  172.16.0.1   2.345ms  2.678ms  2.901ms
```

## Technical Details

- Uses UDP packets for probing
- ICMP for receiving responses
- Raw sockets for packet manipulation
- Dynamic probe management with linked lists
- Configurable port range starting from 33434

## Error Handling

The program handles various error conditions:

- Invalid arguments
- Network unreachable
- Permission denied
- Host resolution failures
- Timeout conditions

## Notes

- Requires root privileges due to raw socket usage
- Similar to standard traceroute but with focused functionality
