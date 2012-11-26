#!/usr/bin/env ruby
#find ./ -name '*.hh' -type f |xargs util/headerreplace.rb
#util/headerreplace.rb *.cc

ARGV.each do |a|
#	print "#{a} "
	File.open(a, 'r+') do |f|
		c = f.read
		#Comment start and comment end
		cstart = c.index('/*')
		if cstart == nil
			STDERR.puts "#{a} No comment at all"
			break
		end
		
		cend = c.index('*/', cstart)
		if cend == nil
			STDERR.puts "#{a} No comment end at all"
			break
		end

		if cstart > 0 && c[0..cstart -1] =~ /\S/
			STDERR.puts "#{a} None whitespace before comment"
			break
		end
		
		#Comment is the first in the file, match it to specials
		comment = c[cstart..cend +1]
		if comment =~ /GPL/ || comment =~ /[Aa]uthor/
			c[cstart..cend +1] = File.new('srcHeader').read
			puts "#{a} DONE"
			f.seek(0)
			f.truncate(0)
			f.seek(0)
			f.write(c)
			break;			
		end
		STDERR.puts "#{a} Not a 'GPL' or 'Author' in first comment"
	end
end
