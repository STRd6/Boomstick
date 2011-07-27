#!/usr/bin/env ruby

# Default to six gamepads if no arguments given
n = (ARGV.shift || 6).to_i

command = ['sudo', 'xboxdrv', '--daemon']

n.times do |i|
  command.push "--next-controller" unless i == 0
  command.push "-i", i.to_s, "--detach-kernel-driver"
end

puts command.join(" ")
system(*command)

