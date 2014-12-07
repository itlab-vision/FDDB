require 'torch'
require 'nn'
require 'image' 

function loadNetModel(path)
	net = torch.load(path)
	net = net:float()
	
end

function predict(img)
	img = torch.FloatTensor(img)

	img = img:view(3, 32, 32)
	img = img:float()

	img = image.rgb2yuv(img)
	local channels = {'y','u','v'}
	local mean = {}
   	local std = {}
   	for i,channel in ipairs(channels) do
        mean[i] = img[{i,{},{} }]:mean()
        std[i] = img[{i,{},{} }]:std()
        img[{ i,{},{} }]:add(-mean[i])
    	img[{ i,{},{} }]:div(std[i])
   	end
   	
   	local neighborhood = image.gaussian1D(5)
   	local normalization = nn.SpatialContrastiveNormalization(1, neighborhood, 1):float()
   	for c in ipairs(channels) do
        img[{ {c},{},{} }] = normalization:forward(img[{{c},{},{} }])
   	end
   	
	output = net:forward(img)
	max = output:max()
	min = output:min()
	for i=1,2 do
		if output[i] == max then
			j = i
			break
		end
	end
	print(output)
	return j, -max, -min
end